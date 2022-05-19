#pragma once

#include "glad/glad.h"

class EBO {
public:
	EBO();
	void set_data(unsigned int* data, GLsizeiptr size, GLenum usage);
	void bind();
	void unbind();

private:
	GLuint ebo;
};
