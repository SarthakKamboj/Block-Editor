#include "vbo.h"

VBO::VBO() {
	glGenBuffers(1, &vbo);
}

void VBO::setData(float* data, GLsizeiptr size, GLenum usage) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}