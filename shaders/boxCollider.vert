#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform mat4 projection;
uniform mat4 view;

void main() {
	mat4 model = translate * rot * scale;
	gl_Position = projection * view * model * vec4(pos, 1.0);
}
