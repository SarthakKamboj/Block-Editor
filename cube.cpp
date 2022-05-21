#include "cube.h"
#include "input/input.h"
#include "cubeEditor.h"
#include "modeManager.h"
#include "renderer/renderer.h"

extern CubeEditor* cubeEditorPtr;
extern ModeManager* modeManagerPtr;

extern int width, height;
extern MouseClickState mouseClickState;
extern MouseState mouseState;

extern bool editorHover;
extern Camera* camPtr;
extern Renderer* rendererPtr;

int Cube::idx = 0;

// extern glm::mat4 projection, view;

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

	const char* transparentVert = "C:\\Sarthak\\voxel_editor\\VoxelEdito\\shaders\\transparent.vert";
	const char* transparentFrag = "C:\\Sarthak\\voxel_editor\\VoxelEdito\\shaders\\transparent.frag";
	transparentProgram = ShaderProgram(transparentVert, transparentFrag);

	outline = false;

	color = glm::vec3(0.0f, 0.43f, 1.0f);

	boxCollider = BoxCollider(transform.pos, transform.scale, transform.rot);

	const char* texture_file_path = "images\\cube_wall.png";
	texture = Texture(texture_file_path, 0);
}

void Cube::update() {
	boxCollider.transform = transform;

	/*
	if (mouseClickState.left && !editorHover) {
		glm::vec2 screenCoords(mouseState.x, mouseState.y);
		Ray ray = boxCollider.screenToLocalRay(screenCoords);

		if (boxCollider.rayCollide(ray)) {
			cubeEditorPtr->cube = this;
			debug_cube.transform.pos = boxCollider.frontColPoint;
		}
	}
	*/

	if (modeManagerPtr->mode != Mode::SELECT) {
		return;
	}

	glm::vec2 screenCoords(mouseState.x, mouseState.y);
	Ray ray = boxCollider.screenToLocalRay(screenCoords);

	if (boxCollider.rayCollide(ray)) {
		if (mouseClickState.left && !editorHover) {
			bool closerToCam = true;
			float dist = 0;
			if (cubeEditorPtr->cube) {
				float curDistToCam = pow(transform.pos.x - camPtr->transform.pos.x, 2) + pow(transform.pos.y - camPtr->transform.pos.y, 2) + pow(transform.pos.z - camPtr->transform.pos.z, 2);
				Transform selectedCubeTransform = cubeEditorPtr->cube->transform;
				float selectedCubeDistToCam = pow(selectedCubeTransform.pos.x - camPtr->transform.pos.x, 2) + pow(selectedCubeTransform.pos.y - camPtr->transform.pos.y, 2) + pow(selectedCubeTransform.pos.z - camPtr->transform.pos.z, 2);
				closerToCam = (curDistToCam <= selectedCubeDistToCam);
			}
			if (closerToCam) {
				cubeEditorPtr->cube = this;
			}
		}
		// debug_cube.transform.pos = boxCollider.frontColPoint;
		// debug_cube.transform.pos = boxCollider.top_col_point;
		for (int i = 0; i < boxCollider.localColPoints.size(); i++) {
			debugCubes[i].transform.pos = boxCollider.localToWorld(boxCollider.localColPoints[i]);
		}
	}
}


void Cube::lateUpdate() {
	outline = (cubeEditorPtr->cube == this);
}

void Cube::setupRenderOutline() {
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

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

	texture.bind();
	rendererPtr->submitShader(shaderProgram, transform);
	shaderProgram.setInt("texUnit", 0);
	shaderProgram.setVec3("inColor", glm::value_ptr(color));

	shaderProgram.bind();
	drawCube();
	shaderProgram.unbind();
	texture.unbind();

	glDisable(GL_STENCIL_TEST);

	for (int i = 0; i < boxCollider.localColPoints.size(); i++) {
		debugCubes[i].render();
	}
}

void Cube::render() {

	/*
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	*/


	if (!outline) {
		/*
		shaderProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));
		shaderProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));
		shaderProgram.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));
		shaderProgram.setMat4("projection", GL_FALSE, mat4GetPtr(projection));
		shaderProgram.setMat4("view", GL_FALSE, mat4GetPtr(view));
		*/

		rendererPtr->submitShader(shaderProgram, transform);

		shaderProgram.setVec3("inColor", glm::value_ptr(color));
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

		/*
		outlineProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));
		outlineProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

		glm::mat4 outlineScaleMat = getScaleMatrix(outlineScale.x * scale.x, outlineScale.y * scale.y, outlineScale.z * scale.z);
		outlineProgram.setMat4("scale", GL_FALSE, mat4GetPtr(outlineScaleMat));

		outlineProgram.setMat4("projection", GL_FALSE, mat4GetPtr(projection));

		outlineProgram.setMat4("view", GL_FALSE, mat4GetPtr(view));
		*/
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

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

void Cube::drawCube() {
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
}
