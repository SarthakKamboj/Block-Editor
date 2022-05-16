#include "cube.h"

extern int height;

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
};

Cube::Cube() {
	vbo.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vbo.unbind();

	vao.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();

	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	outlineScale = glm::vec3(1.05f, 1.05f, 1.05f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	shaderProgram.setFloat("windowHeight", (float)height);

	const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.frag";
	outlineProgram = ShaderProgram(outlineVert, outlineFrag);

	outline = false;

	color = glm::vec3(1.0f, 0.0f, 1.0f);
}

void Cube::render(mat4& projection, mat4& view) {

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	{
		shaderProgram.bind();

		glm::mat4 translationMat = _getTranslationMatrix(pos.x, pos.y, pos.z);
		shaderProgram.setMat4("translate", GL_FALSE, _mat4_get_ptr(translationMat));

		glm::mat4 rotMat = _getRotMatrix(rot.x, rot.y, rot.z);
		shaderProgram.setMat4("rot", GL_FALSE, _mat4_get_ptr(rotMat));

		glm::mat4 scaleMat = _getScaleMatrix(scale.x, scale.y, scale.z);
		shaderProgram.setMat4("scale", GL_FALSE, _mat4_get_ptr(scaleMat));

		shaderProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));

		shaderProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));
		shaderProgram.setVec3("inColor", glm::value_ptr(color));

		drawCube();
		shaderProgram.unbind();

	}

	if (outline) {
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		{
			outlineProgram.bind();

			glm::mat4 translationMat = _getTranslationMatrix(pos.x, pos.y, pos.z);
			outlineProgram.setMat4("translate", GL_FALSE, _mat4_get_ptr(translationMat));

			glm::mat4 rotMat = _getRotMatrix(rot.x, rot.y, rot.z);
			outlineProgram.setMat4("rot", GL_FALSE, _mat4_get_ptr(rotMat));

			glm::mat4 scaleMat = _getScaleMatrix(outlineScale.x * scale.x, outlineScale.y * scale.y, outlineScale.z * scale.z);
			outlineProgram.setMat4("scale", GL_FALSE, _mat4_get_ptr(scaleMat));

			outlineProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));

			outlineProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));

			drawCube();
			outlineProgram.unbind();

		}
	}

}


void Cube::drawCube() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(vertices[0])));
	vao.unbind();
}
