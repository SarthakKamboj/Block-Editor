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
		std::cout << "shader compilation failed" << std::endl;
	}
	else {
		std::cout << "shader compilation succeeded" << std::endl;
	}

	// std::cout << fileContentsChar << std::endl;

	return id;
}
