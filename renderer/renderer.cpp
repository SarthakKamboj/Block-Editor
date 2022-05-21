#include "renderer.h"

extern Camera* camPtr;
extern int width, height;

glm::mat4 projection, view;
float pov;

Renderer::Renderer() {
	pov = 45.0f;
}

void Renderer::submitShader(ShaderProgram& shaderProgram, Transform transform) {
	shaderProgram.setMat4("projection", GL_FALSE, glm::value_ptr(projection));
	shaderProgram.setMat4("view", GL_FALSE, glm::value_ptr(view));

	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	shaderProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);
	shaderProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

	glm::vec3& scale = transform.scale;
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
	projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	view = camPtr->getViewMat();
}
