#include "plane.h"
#include "renderer/renderer.h"

extern Renderer* rendererPtr;

static float vertices[] = {
	-0.5f, 0.0f, 0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, -0.5f,
	0.5f, 0.0f, -0.5f
};

static unsigned int indicies[] = {
	0,1,2,
	1,2,3
};

Plane::Plane() {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\plane.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\plane.frag";

	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	glm::vec3 color(0.75f, 0.75f, 0.75f);
	shaderProgram.setVec3("color", glm::value_ptr(color));

	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Plane::render() {

	rendererPtr->submitShader(shaderProgram, transform);

	shaderProgram.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	shaderProgram.unbind();
}
