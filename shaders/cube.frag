#version 330 core

in vec2 tex;

out vec4 FragColor;

uniform sampler2D texUnit;
uniform vec3 color;

void main() {
	vec4 texColor = texture(texUnit, tex);
	if (texColor.r > 0.8 && texColor.g > 0.8 && texColor.b > 0.8) {
		float val = 0.15;
		FragColor = vec4(val, val, val, 1.0);
	} else {
		FragColor = vec4(color, 1.0);
	}
}
