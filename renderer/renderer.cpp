#include "renderer.h"
#include "cameraEditor.h"

extern CameraEditor* cameraEditorPtr;
extern int width, height;

glm::mat4 projection, view;
float pov;

Renderer::Renderer() {
	pov = 45.0f;
	debugMode = false;
}

static bool debuggedBefore = false;
void Renderer::enableDebugMode() {
	debugMode = true;
	prevCamera = cameraEditorPtr->cam;
	cameraEditorPtr->cam = &debugCamera;
	if (!debuggedBefore) {
		debugCamera.transform = prevCamera->transform;
		debuggedBefore = true;
	}
	else {
		debugCamera.transform = prevDebugCamTransform;
	}
}

void Renderer::disableDebugMode() {
	debugMode = false;
	cameraEditorPtr->cam = prevCamera;
}

void Renderer::toggleDebugMode() {
	if (debugMode) {
		disableDebugMode();
	}
	else {
		enableDebugMode();
	}
}

void Renderer::submitShaderWithoutTransform(ShaderProgram& shaderProgram) {
	shaderProgram.setMat4("projection", GL_FALSE, glm::value_ptr(projection));
	shaderProgram.setMat4("view", GL_FALSE, glm::value_ptr(view));
}

bool Renderer::isInDebugMode() {
	return debugMode;
}

void Renderer::submitShader(ShaderProgram& shaderProgram, Transform transform) {
	shaderProgram.setMat4("projection", GL_FALSE, glm::value_ptr(projection));
	shaderProgram.setMat4("view", GL_FALSE, glm::value_ptr(view));

	glm::vec3 pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	shaderProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));

	glm::vec3 rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);
	shaderProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

	glm::vec3 scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	shaderProgram.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));
}

void Renderer::clear() {
	glm::vec3 clearColor(0.0f, 0.0f, 0.0f);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClearStencil(0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::frameSetup() {
	/*
	if (debugMode) {
		projection = getProjectionMatrix(45.0f, 0.1f, 100.0f, ((float)width) / height);
	}
	else {
		projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}
	*/

	// projection = getProjectionMatrix(45.0f, 0.1f, 100.0f, ((float)width) / height);
	projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	view = cameraEditorPtr->cam->getViewMat();
	printMat4(view);
	std::cout << std::endl;
	prevDebugCamTransform = debugCamera.transform;
}
