#include "debugCube.h"
#include "renderer/renderer.h"

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

void DebugCube::setColor(glm::vec3 color) {
	shaderProgram.setVec3("color", glm::value_ptr(color));
}

void DebugCube::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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