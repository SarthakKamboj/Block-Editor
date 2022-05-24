#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform mat4 projection;
uniform mat4 view;

void main() {
	vec4 newPos = vec4(aPos, 1.0);
	mat4 model = translate * rot * scale;
	gl_Position = projection * view * model * newPos;
}