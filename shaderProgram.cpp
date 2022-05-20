#include "shaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram() {
	program_id = -1;
}

ShaderProgram::ShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
	GLuint vertexId = create_shader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentId = create_shader(fragmentFilePath, GL_FRAGMENT_SHADER);
	shaderPath = vertexFilePath;

	program_id = glCreateProgram();
	glAttachShader(program_id, vertexId);
	glAttachShader(program_id, fragmentId);
	glLinkProgram(program_id);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void ShaderProgram::bind() {
	if (program_id == -1) return;
	glUseProgram(program_id);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

GLuint ShaderProgram::create_shader(const char* filePath, GLenum shaderType) {
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

void ShaderProgram::set_int(const GLchar* varName, int value) {
	if (program_id == -1) return;
	GLint cur_program_id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cur_program_id);
	if (cur_program_id != program_id) {
		bind();
	}
	GLint location = get_variable_location(varName);
	if (location == -1) {
		glUniform1i(location, value);
	}
	if (cur_program_id != program_id) {
		unbind();
	}
}

void ShaderProgram::set_float(const GLchar* varName, float value) {
	if (program_id == -1) return;
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != program_id) {
		bind();
	}
	GLint location = get_variable_location(varName);
	if (location != -1) {
		glUniform1f(location, value);
	}
	if (curProgramId != program_id) {
		unbind();
	}
}

void ShaderProgram::set_vec_3(const GLchar* varName, const GLfloat* vec3) {
	if (program_id == -1) return;
	GLint curProgramId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != program_id) {
		bind();
	}
	GLint location = get_variable_location(varName);
	if (location != -1) {
		glUniform3fv(location, 1, vec3);
	}
	if (curProgramId != program_id) {
		unbind();
	}
}


void ShaderProgram::set_mat_4(const GLchar* varName, GLboolean transpose, const GLfloat* mat) {
	if (program_id == -1) return;
	GLint curProgramId = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &curProgramId);
	if (curProgramId != program_id) {
		bind();
	}

	GLint location = get_variable_location(varName);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, transpose, mat);
	}
	if (curProgramId != program_id) {
		unbind();
	}
}

GLint ShaderProgram::get_variable_location(const GLchar* varName) {
	GLint location = glGetUniformLocation(program_id, varName);
	if (location == -1) {
		std::cout << "uniform with name " << varName << " does not exist in this shader program" << std::endl;
		std::cout << shaderPath << std::endl;
	}
	return location;
}
