#version 330 core

in vec3 color;

out vec4 FragColor;
uniform float windowHeight;

uniform float msTime;
uniform float loopDuration;

#define M_PI 3.1415926535897932384626433832795

void main() {
	// float rad = 2 * M_PI * msTime / 1000 / (loopDuration / 2.0f);
	// FragColor = mix(vec4(cos(rad), sin(rad), cos(rad), 1.0), vec4(sin(rad), cos(rad), sin(rad), 1.0), gl_FragCoord.y / windowHeight);
	FragColor = vec4(color, 1.0);
}