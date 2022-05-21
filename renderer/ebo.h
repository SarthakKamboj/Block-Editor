#pragma once

#include "glad/glad.h"

class EBO {
public:
	EBO();
	void setData(unsigned int* data, GLsizeiptr size, GLenum usage);
	void bind();
	void unbind();

private:
	GLuint ebo;
};
