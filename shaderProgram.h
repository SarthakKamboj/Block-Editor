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
	void setUniformF(const GLchar* varName, float value);
	void setVec3(const GLchar* varName, const GLfloat* vec3);

private:
	GLuint programId;
	GLuint createShader(const char* filePath, GLenum shaderType);
};
