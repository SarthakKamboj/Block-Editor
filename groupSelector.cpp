#include "groupSelector.h"
#include "input/input.h"
#include "glm/gtc/type_ptr.hpp"
#include "cube.h"
#include "cubeEditor.h"
#include "helper/helper.h"
#include "modeManager.h"

extern MouseClickState mouseDownState;
extern MouseClickState mousePressedState;
extern MouseState mouseState;
extern ModeManager* modeManagerPtr;

static float vertices[8];
static unsigned int indicies[6] = {
	0,1,2,
	1,2,3
};

GroupSelector::GroupSelector() {

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\groupSelector.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\groupSelector.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	glm::vec3 color(0.2f, 0.2f, 0.2f);
	shaderProgram.setVec3("color", glm::value_ptr(color));

	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vao.bind();
	vao.setAttribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	ebo.bind();
	vao.unbind();

	activelySelecting = false;
}

extern std::vector<Cube> cubes;
extern CubeEditor* cubeEditorPtr;
extern bool editorHover;
void GroupSelector::update() {

	if (modeManagerPtr->mode != Mode::SELECT) {
		activelySelecting = false;
		return;
	}

	if (editorHover) return;

	if (mousePressedState.left) {
		activelySelecting = true;
		topLeftScreen = glm::vec2(mouseState.x, mouseState.y);
		bottomRightScreen = glm::vec2(mouseState.x, mouseState.y);
		updateVertices();
	}
	else if (mouseDownState.left) {
		bottomRightScreen = glm::vec2(mouseState.x, mouseState.y);
		updateVertices();
	}
	else {
		activelySelecting = false;
	}

	if (!activelySelecting) return;

	for (int cubeIdx = 0; cubeIdx < cubes.size(); cubeIdx++) {
		for (int i = 0; i < 6; i++) {
			glm::vec3 localPoint = { BoxCollider::vertices[(i * 3)], BoxCollider::vertices[(i * 3) + 1], BoxCollider::vertices[(i * 3) + 2] };
			glm::vec3 cubeVertNdc = cubes[cubeIdx].boxCollider.localToNDC(localPoint);

			float largerNdcX = fmax(topLeftNdc.x, topRightNdc.x);
			float smallerNdcX = fmin(topLeftNdc.x, topRightNdc.x);
			float largerNdcY = fmax(bottomRightNdc.y, topRightNdc.y);
			float smallerNdcY = fmin(bottomRightNdc.y, topRightNdc.y);

			if (cubeVertNdc.x >= smallerNdcX && cubeVertNdc.x <= largerNdcX) {
				if (cubeVertNdc.y >= smallerNdcY && cubeVertNdc.y <= largerNdcY) {
					if (cubeVertNdc.z >= 0.1f && cubeVertNdc.z <= 100.0f) {
						cubeEditorPtr->addCube(&cubes[cubeIdx]);
					}
				}
			}
		}
	}

}

void GroupSelector::updateVertices() {
	float width = bottomRightScreen.x - topLeftScreen.x, height = bottomRightScreen.y - topLeftScreen.y;

	topRightScreen = glm::vec2(topLeftScreen.x + width, topLeftScreen.y);
	bottomLeftScreen = glm::vec2(topLeftScreen.x, topLeftScreen.y + height);

	topLeftNdc = Input::screenToNdc(topLeftScreen.x, topLeftScreen.y);
	topRightNdc = Input::screenToNdc(topRightScreen.x, topRightScreen.y);
	bottomLeftNdc = Input::screenToNdc(bottomLeftScreen.x, bottomLeftScreen.y);
	bottomRightNdc = Input::screenToNdc(bottomRightScreen.x, bottomRightScreen.y);

	vertices[0] = topLeftNdc.x;
	vertices[1] = topLeftNdc.y;

	vertices[2] = topRightNdc.x;
	vertices[3] = topRightNdc.y;

	vertices[4] = bottomLeftNdc.x;
	vertices[5] = bottomLeftNdc.y;

	vertices[6] = bottomRightNdc.x;
	vertices[7] = bottomRightNdc.y;
}

void GroupSelector::render() {

	if (modeManagerPtr->mode != Mode::SELECT) {
		activelySelecting = false;
		return;
	}

	if (!activelySelecting) return;

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	shaderProgram.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	shaderProgram.unbind();
}

