#include "grid.h"
#include "stb_image.h"
#include "input/input.h"
#include "cube.h"
#include "modeManager.h"
#include "renderer/renderer.h"

static float scale = 20.0f;

extern MouseClickState mouseClickState;
extern MouseState mouseState;
extern bool editorHover;
extern std::vector<Cube> cubes;
extern Camera* camPtr;
extern ModeManager* modeManagerPtr;
extern Renderer* rendererPtr;

static float vertices[] = {
	0.5f, 0.5f, scale, scale,
	-0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, scale,
	0.5f, -0.5f, scale, 0.0f
};

static unsigned int indicies[] = {
	0,2,1,3,1,0
};

// extern glm::mat4 projection, view;

Grid::Grid() {

	glm::vec3 unit(1.0f, 1.0f, 1.0f);
	transform = Transform(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(90.0f, 0.0f, 0.0f), unit * scale);

	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	vao.unbind();
	ebo.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\grid.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\grid.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);

	textureUnit = 0;

	const char* filePath = "images\\grid.png";
	texture = Texture(filePath, textureUnit);

	boxCollider = BoxCollider(transform.pos, glm::vec3(scale, scale, 0.1f), transform.rot);
}

void Grid::update() {

	if (modeManagerPtr->mode != Mode::ADD) {
		return;
	}

	glm::vec2 screenCoords(mouseState.x, mouseState.y);
	Ray ray = boxCollider.screenToLocalRay(screenCoords);

	if (!editorHover && boxCollider.rayCollide(ray)) {
		for (int i = 0; i < boxCollider.localColPoints.size(); i++) {
			debugCubes[i].transform.pos = boxCollider.localToWorld(boxCollider.localColPoints[i]);
		}
		if (mouseClickState.left) {
			Cube newCube;
			glm::vec3 pos;
			float closestDist = -1;
			for (int i = 0; i < boxCollider.localColPoints.size(); i++) {
				glm::vec3 colWorldPos = boxCollider.localToWorld(boxCollider.localColPoints[0]);
				glm::vec3 camWorldPos = camPtr->transform.pos;
				float dist = pow(camWorldPos.x - colWorldPos.x, 2) + pow(camWorldPos.y - colWorldPos.y, 2) + pow(camWorldPos.z - colWorldPos.z, 2);
				if (closestDist == -1) {
					closestDist = dist;
					pos = colWorldPos;
				}
				else if (dist < closestDist) {
					closestDist = dist;
					pos = colWorldPos;
				}
			}
			pos += glm::vec3(0.0f, 0.5f, 0.0f);
			pos = glm::vec3(round(pos.x), round(pos.y), round(pos.z));
			bool create = true;
			for (int i = 0; i < cubes.size(); i++) {
				glm::vec3& cubePos = cubes[i].transform.pos;
				if (cubePos.x == pos.x && cubePos.y == pos.y && cubePos.z == pos.z) {
					create = false;
				}
			}
			if (create) {
				newCube.transform.pos = pos;
				cubes.push_back(newCube);
			}
		}
	}
}

void Grid::render() {
	/*
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	shaderProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);
	shaderProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	shaderProgram.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));

	shaderProgram.setMat4("projection", GL_FALSE, mat4GetPtr(projection));
	shaderProgram.setMat4("view", GL_FALSE, mat4GetPtr(view));
	*/

	rendererPtr->submitShader(shaderProgram, transform);

	shaderProgram.setInt("texUnit", textureUnit);
	shaderProgram.bind();

	texture.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	shaderProgram.unbind();
	texture.unbind();

	boxCollider.render();

	for (int i = 0; i < boxCollider.localColPoints.size(); i++) {
		debugCubes[i].render();
	}
}