#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "glad/glad.h"

class ShaderProgram {
public:
	ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath);
	void bind();
	void unbind();
	void setFloat(const GLchar* varName, float value);
	void setVec3(const GLchar* varName, const GLfloat* vec3);
	void setMat4(const GLchar* varName, GLboolean transpose, const GLfloat* mat);

private:
	GLuint programId;
	GLuint createShader(const char* filePath, GLenum shaderType);
};
