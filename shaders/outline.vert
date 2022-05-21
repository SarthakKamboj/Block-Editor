#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

uniform mat4 projection;
uniform mat4 view;

out vec3 color;

void main() {
	vec4 newPos = vec4(aPos, 1.0);
    mat4 model = translate * rot * scale;
    gl_Position = projection * view * model * newPos;
    color = aColor;
}
