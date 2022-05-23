#include "line.h"
#include "renderer.h"

extern Renderer* rendererPtr;

Line::Line() {
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;
	vertices[4] = 5.0f;
	vertices[5] = 0.0f;

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertPath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\line.vert";
	const char* fragPath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\line.frag";
	lineProgram = ShaderProgram(vertPath, fragPath);

	lineProgram.setVec3("color", glm::value_ptr(glm::vec3(1.0f, 0.0f, 1.0f)));
}

void Line::setStartPos(glm::vec3 _pos) {
	vertices[0] = _pos.x;
	vertices[1] = _pos.y;
	vertices[2] = _pos.z;
}

void Line::setColor(glm::vec3 color) {
	lineProgram.setVec3("color", glm::value_ptr(color));
}

void Line::setEndPos(glm::vec3 _pos) {
	vertices[3] = _pos.x;
	vertices[4] = _pos.y;
	vertices[5] = _pos.z;
}

void Line::render() {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	rendererPtr->submitShaderWithoutTransform(lineProgram);

	glEnable(GL_DEPTH_TEST);
	lineProgram.bind();
	vao.bind();
	glDrawArrays(GL_LINES, 0, sizeof(vertices) / sizeof(vertices[0]));
	lineProgram.bind();
	vao.unbind();
}
