#pragma once

#include "glad/glad.h"
#include "VBO.h"

class VAO {
public:
	VAO();
	void set_attribute(VBO& vbo, GLuint index, GLuint size, GLenum type, GLsizei stride, const void* offset);
	void bind();
	void unbind();

private:
	GLuint vao;
};
