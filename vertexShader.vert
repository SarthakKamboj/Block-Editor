#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform vec3 inColor;

void main() {

	vec4 newPos = vec4(aPos, 1.0);
	gl_Position = translate * rot * scale * newPos;

	color = inColor;
}