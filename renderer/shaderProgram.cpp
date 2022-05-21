#include "shaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram() {
	programId = -1;
	shaderPath = "no shader path provided";
}

ShaderProgram::ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
	GLuint vertexId = createShader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentId = createShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	shaderPath = vertexFilePath;

	programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void ShaderProgram::bind() {
	if (programId == -1) return;
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != programId) {
		glUseProgram(programId);
	}
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

GLuint ShaderProgram::createShader(const char* filePath, GLenum shaderType) {
	std::string line, fileContents;
	std::ifstream file(filePath);

	while (std::getline(file, line)) {
		fileContents += line + "\n";
	}

	const char* fileContentsChar = fileContents.c_str();
	GLuint id = glCreateShader(shaderType);
	glShaderSource(id, 1, &fileContentsChar, NULL);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		std::cout << "shader compilation failed for shader of type " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << shaderPath << std::endl;
		int maxErrorLength = 1024;
		char errorInfo[1024];
		glGetShaderInfoLog(id, maxErrorLength, &maxErrorLength, errorInfo);
		std::cout << "ERROR: " << errorInfo << std::endl;
		glDeleteShader(id);
	}

	return id;
}

void ShaderProgram::setInt(const GLchar* varName, int value) {
	if (programId == -1) return;
	bind();
	GLint location = getVariableLocation(varName);
	if (location == -1) {
		glUniform1i(location, value);
	}
	unbind();
}

void ShaderProgram::setFloat(const GLchar* varName, float value) {
	if (programId == -1) return;
	bind();
	GLint location = getVariableLocation(varName);
	if (location != -1) {
		glUniform1f(location, value);
	}
	unbind();
}

void ShaderProgram::setVec3(const GLchar* varName, const GLfloat* vec3) {
	if (programId == -1) return;
	bind();
	GLint location = getVariableLocation(varName);
	if (location != -1) {
		glUniform3fv(location, 1, vec3);
	}
	unbind();
}


void ShaderProgram::setMat4(const GLchar* varName, GLboolean transpose, const GLfloat* mat) {
	if (programId == -1) return;
	bind();
	GLint location = getVariableLocation(varName);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, transpose, mat);
	}
	unbind();
}

// TODO: figure out why location shaderPath printing causing error
GLint ShaderProgram::getVariableLocation(const GLchar* varName) {
	if (programId == -1) return -1;
	GLint location = glGetUniformLocation(programId, varName);
	if (location == -1) {
		std::cout << "uniform with name " << varName << " does not exist in this shader program" << std::endl;
		std::cout << shaderPath << std::endl;
	}
	return location;
}
