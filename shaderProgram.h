#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "glad/glad.h"

class ShaderProgram {
public:
	ShaderProgram();
	ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath);
	void bind();
	void unbind();
	void set_float(const GLchar* varName, float value);
	void set_vec_3(const GLchar* varName, const GLfloat* vec3);
	void set_mat_4(const GLchar* varName, GLboolean transpose, const GLfloat* mat);

private:
	GLuint program_id;
	GLuint create_shader(const char* filePath, GLenum shaderType);
};
