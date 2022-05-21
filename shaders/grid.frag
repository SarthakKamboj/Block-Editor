#version 330 core

uniform sampler2D texUnit;

out vec4 FragColor;

in vec2 texCoord;

void main() {
	vec4 texColor = texture(texUnit, texCoord);
	float avgSquare = (pow(texColor.r,2) + pow(texColor.g,2) + pow(texColor.b,2)) / 3;
	if (avgSquare > 0.001) {
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	FragColor = texColor;
}