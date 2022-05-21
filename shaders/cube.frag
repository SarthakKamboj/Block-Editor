#version 330 core

in vec2 tex;

out vec4 FragColor;

uniform sampler2D texUnit;
uniform vec3 inColor;

void main() {
	vec4 texColor = texture(texUnit, tex);
	FragColor = texColor * vec4(inColor, 1.0);
	if (texColor.r == 0 && texColor.g == 0 && texColor.b == 0) {
		float val = 0.15;
		FragColor = vec4(val, val, val, 1.0);
	}
}
