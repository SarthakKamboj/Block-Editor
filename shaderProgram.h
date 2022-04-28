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

private:
	GLuint programId;
	GLuint createShader(const char* filePath, GLenum shaderType);
};
