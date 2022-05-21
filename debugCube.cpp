#include "debugCube.h"
#include "renderer/renderer.h"

// extern glm::mat4 projection, view;
extern Renderer* rendererPtr;

static float vertices[] = {
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
};

static unsigned int indicies[] = {
	0,5,1,0,4,5,
	4,5,6,5,6,7,
	1,0,3,3,2,0,
	7,2,6,7,3,2,
	5,6,7,5,6,1,
	4,3,0,4,3,6
};

DebugCube::DebugCube() {

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
	ebo.unbind();

	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	const char* vertex_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\boxCollider.vert";
	const char* fragment_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	shaderProgram = ShaderProgram(vertex_file_path, fragment_file_path);

	shaderProgram.setVec3("color", glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
}

void DebugCube::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);

	shaderProgram.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));
	shaderProgram.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));
	shaderProgram.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));
	shaderProgram.setMat4("projection", GL_FALSE, mat4GetPtr(projection));
	shaderProgram.setMat4("view", GL_FALSE, mat4GetPtr(view));
	*/

	rendererPtr->submitShader(shaderProgram, transform);

	shaderProgram.bind();
	drawCube();
	shaderProgram.unbind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void DebugCube::drawCube() {
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
}