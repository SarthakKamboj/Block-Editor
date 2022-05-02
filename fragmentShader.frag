#version 330 core

in vec3 color;

out vec4 FragColor;

uniform float windowHeight;

void main() {
	FragColor = vec4((gl_FragCoord.y / windowHeight) * color, 1.0);
}