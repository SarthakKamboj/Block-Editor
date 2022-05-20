#version 330 core

uniform vec3 color;

out vec4 FragColor;

in vec2 texCoord;

void main() {

	FragColor = vec4(color, 1.0);
	// FragColor = texture(0, texCoord);
}