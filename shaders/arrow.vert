#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTex;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform mat4 projection;
uniform mat4 view;

out vec2 tex;

void main() {
	mat4 model = translate * rot * scale;
	gl_Position = projection * view * model * vec4(pos, 1.0);
	tex = aTex;
}