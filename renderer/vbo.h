#pragma once

#include "glad/glad.h"

class VBO {
public:
	VBO();
	void setData(float* data, GLsizeiptr size, GLenum usage);
	void bind();
	void unbind();

private:
	GLuint vbo;
};
