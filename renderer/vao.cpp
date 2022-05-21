#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &vao);
}

void VAO::setAttribute(VBO& vbo, GLuint index, GLuint size, GLenum type, GLsizei stride, const void* offset) {
	vbo.bind();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
	vbo.unbind();
}

void VAO::bind() {
	glBindVertexArray(vao);
}

void VAO::unbind() {
	glBindVertexArray(0);
}
