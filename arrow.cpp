#include "arrow.h"

static float vertices[] = {
	-0.1f, 0.0f,
	0.1f, 0.0f,
	0.1f, 0.7f,

	-0.1f, 0.7f,
	-0.1f, 0.0f,
	0.1f, 0.7f,

	0.3f, 0.7f,
	0.0f, 1.0f,
	-0.3f, 0.7f
};

Arrow::Arrow(glm::vec3 _color) {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	vao.setAttribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	arrowShader = ShaderProgram(vertexFilePath, fragmentFilePath);
	scale = glm::vec3(0.3f, 0.5f, 0.5f);
	color = _color;
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
	arrowShader.setVec3("color", glm::value_ptr(color));
}

void Arrow::render(glm::mat4& projection, glm::mat4& view) {


	arrowShader.bind();
	glm::mat4 translationMat = _getTranslationMatrix(pos.x, pos.y, pos.z);
	arrowShader.setMat4("translate", GL_FALSE, _mat4_get_ptr(translationMat));

	glm::mat4 rotMat = _getRotMatrix(rot.x, rot.y, rot.z);
	arrowShader.setMat4("rot", GL_FALSE, _mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = _getScaleMatrix(scale.x, scale.y, scale.z);
	arrowShader.setMat4("scale", GL_FALSE, _mat4_get_ptr(scaleMat));

	arrowShader.setMat4("projection", GL_FALSE, _mat4_get_ptr(projection));

	arrowShader.setMat4("view", GL_FALSE, _mat4_get_ptr(view));

	glDisable(GL_DEPTH_TEST);
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));
	vao.unbind();

	arrowShader.unbind();
	glEnable(GL_DEPTH_TEST);
}