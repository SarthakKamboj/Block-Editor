#include "shaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
	GLuint vertexId = createShader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentId = createShader(fragmentFilePath, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void ShaderProgram::bind() {
	glUseProgram(programId);
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
		int maxErrorLength = 1024;
		char errorInfo[1024];
		glGetShaderInfoLog(id, maxErrorLength, &maxErrorLength, errorInfo);
		std::cout << "ERROR: " << errorInfo << std::endl;
		glDeleteShader(id);
	}
	else {
		std::cout << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compilation succeeded" << std::endl;
	}

	return id;
}


void ShaderProgram::setUniformF(const GLchar* varName, float value) {
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != programId) {
		bind();
	}
	GLint location = glGetUniformLocation(programId, varName);
	if (location == -1) {
		std::cout << "uniform with name " << varName << " does not exist in this shader program" << std::endl;
	}
	else {
		glUniform1f(location, value);
	}
	if (curProgramId != programId) {
		unbind();
	}
}

void ShaderProgram::setVec3(const GLchar* varName, const GLfloat* vec3) {
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != programId) {
		bind();
	}
	GLint location = glGetUniformLocation(programId, varName);
	if (location == -1) {
		std::cout << "uniform with name " << varName << " does not exist in this shader program" << std::endl;
	}
	else {
		glUniform3fv(location, 1, vec3);
	}
	if (curProgramId != programId) {
		unbind();
	}
}


void ShaderProgram::setMat4(const GLchar* varName, GLboolean transpose, const GLfloat* mat) {
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != programId) {
		bind();
	}
	GLint location = glGetUniformLocation(programId, varName);
	if (location == -1) {
		std::cout << "uniform with name " << varName << " does not exist in this shader program" << std::endl;
	}
	else {
		glUniformMatrix4fv(location, 1, transpose, mat);
	}
	if (curProgramId != programId) {
		unbind();
	}
}
