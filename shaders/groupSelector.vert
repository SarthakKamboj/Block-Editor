#version 330 core

layout (location = 0) in vec2 ndcCoord;

void main() {
	gl_Position = vec4(ndcCoord, -1.0, 1.0);
}