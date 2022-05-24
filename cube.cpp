#include "cube.h"
#include "input/input.h"
#include "cubeEditor.h"
#include "modeManager.h"
#include "renderer/renderer.h"
#include "groupSelector.h"

extern CubeEditor* cubeEditorPtr;
extern ModeManager* modeManagerPtr;
extern GroupSelector* groupSelectorPtr;

extern int width, height;
extern MouseClickState mousePressedState;
extern MouseState mouseState;

extern bool editorHover;
extern Camera* camPtr;
extern Renderer* rendererPtr;
extern std::map<SDL_Keycode, bool> keyPressedMap;
extern std::map<SDL_Keycode, bool> keyDownMap;

int Cube::idx = 0;

static float vertices[] = {
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0
};

static unsigned int indicies[] = {
	0,5,1,0,4,5,
	4,5,6,5,6,7,
	1,0,3,3,2,0,
	7,2,6,7,3,2,
	5,9,8,5,9,1,
	4,11,0,4,11,10
};

Cube::Cube() {

	name = "Cube " + std::to_string(Cube::idx);
	Cube::idx += 1;

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();
	ebo.unbind();

	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	outlineScale = glm::vec3(1.05f, 1.05f, 1.05f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\cube.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\cube.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);

	const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\outline.frag";
	outlineProgram = ShaderProgram(outlineVert, outlineFrag);

	const char* transparentVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\transparent.vert";
	const char* transparentFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\transparent.frag";
	transparentProgram = ShaderProgram(transparentVert, transparentFrag);

	outline = false;

	color = glm::vec3(0.0f, 0.43f, 1.0f);

	boxCollider = BoxCollider(transform.pos, transform.scale, transform.rot);

	const char* texFilePath = "images\\cube_wall.png";
	texture = Texture(texFilePath, 0);
}

void Cube::update() {
	boxCollider.transform = transform;

	if (modeManagerPtr->mode != Mode::SELECT || rendererPtr->isInDebugMode()) {
		return;
	}

	if (mousePressedState.left && !editorHover) {
		glm::vec2 screenCoords(mouseState.x, mouseState.y);
		Ray ray = boxCollider.screenToLocalRay(screenCoords);

		if (boxCollider.rayCollide(ray)) {
			bool closerToCam = true;
			float dist = 0;
			if (cubeEditorPtr->cubeClickedOn) {
				float curDistToCam = pow(transform.pos.x - camPtr->transform.pos.x, 2) + pow(transform.pos.y - camPtr->transform.pos.y, 2) + pow(transform.pos.z - camPtr->transform.pos.z, 2);
				Transform selectedCubeTransform = cubeEditorPtr->cubeClickedOn->transform;
				float selectedCubeDistToCam = pow(selectedCubeTransform.pos.x - camPtr->transform.pos.x, 2) + pow(selectedCubeTransform.pos.y - camPtr->transform.pos.y, 2) + pow(selectedCubeTransform.pos.z - camPtr->transform.pos.z, 2);
				closerToCam = (curDistToCam <= selectedCubeDistToCam);
			}

			if (closerToCam) {
				cubeEditorPtr->cubeClickedOn = this;
			}
		}
	}

	// if (!groupSelectorPtr->activelySelecting) return;

	/*
	glm::vec2 points[4] = {
		groupSelectorPtr->topLeftScreen,
		groupSelectorPtr->topRightScreen,
		groupSelectorPtr->bottomLeftScreen,
		groupSelectorPtr->bottomRightScreen
	};

	for (int i = 0; i < 4; i++) {
		Ray r = boxCollider.screenToLocalRay(points[i]);
		if (boxCollider.rayCollide(r)) {
			cubeEditorPtr->addCube(this);
		}
	}
	*/
}


void Cube::lateUpdate() {
	outline = false;
	for (int i = 0; i < cubeEditorPtr->selectedCubes.size(); i++) {
		if (cubeEditorPtr->selectedCubes[i] == this) {
			outline = true;
			return;
		}
	}
}

void Cube::setupRenderOutline() {
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	texture.bind();
	rendererPtr->submitShader(shaderProgram, transform);
	shaderProgram.setInt("texUnit", 0);
	shaderProgram.setVec3("color", glm::value_ptr(color));

	shaderProgram.bind();
	drawCube();
	shaderProgram.unbind();
	texture.unbind();

	glDisable(GL_STENCIL_TEST);

}

void Cube::render() {

	if (!outline) {
		rendererPtr->submitShader(shaderProgram, transform);

		shaderProgram.setVec3("color", glm::value_ptr(color));
		shaderProgram.setInt("texUnit", 0);

		texture.bind();
		shaderProgram.bind();
		drawCube();
		shaderProgram.unbind();
		texture.unbind();
	}
	else {
		outlineProgram.bind();
		Transform outlineTransform = transform;
		outlineTransform.scale = outlineScale * transform.scale;
		rendererPtr->submitShader(outlineProgram, outlineTransform);
		outlineProgram.unbind();
	}

}


void Cube::renderOutline() {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	outlineProgram.bind();
	drawCube();
	outlineProgram.unbind();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
}

void Cube::drawCube() {
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
}
