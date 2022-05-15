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

    pos = vec3(0.0f, 0.0f, 0.0f);
    scale = vec3(1.0f, 1.0f, 1.0f);
    outlineScale = vec3(1.05f, 1.05f, 1.05f);
    rot = vec3(0.0f, 0.0f, 0.0f);

    const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	shaderProgram.setFloat("windowHeight", (float)height);

    const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.frag";
	outlineProgram = ShaderProgram(outlineVert, outlineFrag);

    outline = false;

    color = vec3(1.0f, 0.0f, 1.0f);
}

void Cube::render(mat4& projection, mat4& view) {

		glStencilFunc(GL_ALWAYS, 1, 0xFF);

		{
			shaderProgram.bind();

			mat4 translationMat = getTranslationMatrix(pos.coords.x, pos.coords.y, pos.coords.z);
			shaderProgram.setMat4("translate", GL_TRUE, mat4_get_ptr(translationMat));

			mat4 rotMat = getRotMatrix(rot.coords.x, rot.coords.y, rot.coords.z);
			shaderProgram.setMat4("rot", GL_TRUE, mat4_get_ptr(rotMat));

			mat4 scaleMat = getScaleMatrix(scale.coords.x, scale.coords.y, scale.coords.z);
			shaderProgram.setMat4("scale", GL_TRUE, mat4_get_ptr(scaleMat));

			shaderProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));

			shaderProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));
			shaderProgram.setVec3("inColor", vec3_get_ptr(color));

			drawCube();
			shaderProgram.unbind();

		}

		if (outline) {
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			{
				outlineProgram.bind();

				mat4 translationMat = getTranslationMatrix(pos.coords.x, pos.coords.y, pos.coords.z);
				outlineProgram.setMat4("translate", GL_TRUE, mat4_get_ptr(translationMat));

				mat4 rotMat = getRotMatrix(rot.coords.x, rot.coords.y, rot.coords.z);
				outlineProgram.setMat4("rot", GL_TRUE, mat4_get_ptr(rotMat));

				mat4 scaleMat = getScaleMatrix(outlineScale.coords.x, outlineScale.coords.y, outlineScale.coords.z);
				outlineProgram.setMat4("scale", GL_TRUE, mat4_get_ptr(scaleMat));

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
