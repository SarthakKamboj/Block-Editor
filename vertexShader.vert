#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float msTime;
uniform float loopDuration;

uniform vec3 uniformColor;
// uniform vec3 pos; 
// uniform vec3 scale;
// uniform vec3 eulerAngles;

#define M_PI 3.1415926535897932384626433832795

void main() {

	float rad = 2 * M_PI * msTime / 1000 / loopDuration;
	/*
	float xOffset = sin(rad) * 0.5f;
	float yOffset = cos(rad) * 0.5f;
	gl_Position = vec4(aPos + vec3(xOffset, yOffset, 0), 1.0);
	*/
	// gl_Position = vec4(aPos, 1.5 + sin(rad));
	gl_Position = vec4(aPos, 1.0);
	color = aColor;
	color = uniformColor;
}