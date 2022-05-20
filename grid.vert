#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform mat4 projection;
uniform mat4 view;

out vec2 texCoord;

void main() {
	mat4 model = translate * rot * scale;
	texCoord = aTex;
	gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
}