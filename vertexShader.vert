#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rot;

// uniform mat4 modelMat;

// uniform vec3 pos; 
// uniform vec3 scale;
// uniform vec3 eulerAngles;

// #define M_PI 3.1415926535897932384626433832795
// #define DEG_2_RAD (M_PI / 180.0)

/*
mat4 getRotMat() {
	float xRot = eulerAngles.x * DEG_2_RAD;
	float yRot = eulerAngles.y * DEG_2_RAD;
	float zRot = eulerAngles.z * DEG_2_RAD;

	mat4 xRotMat = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, cos(xRot), sin(xRot), 0.0,
		0.0, -sin(xRot), cos(xRot), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	mat4 yRotMat = mat4(
		cos(yRot), 0.0, -sin(yRot), 0.0,
		0.0, 1.0, 0.0, 0.0,
		sin(yRot), 0.0, cos(yRot), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	mat4 zRotMat = mat4(
		cos(zRot), sin(zRot), 0.0, 0.0,
		-sin(zRot), cos(zRot), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	return transpose(zRotMat) * transpose(yRotMat) * transpose(xRotMat);
}

mat4 getModelMatrix() {
	float xScale = scale.x;
	float yScale = scale.y;
	float zScale = scale.z;

	mat4 scaleMat = mat4(
		xScale, 0.0, 0.0, 0.0,
		0.0, yScale, 0.0, 0.0,
		0.0, 0.0, zScale, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	mat4 rotMat = getRotMat();

	float xPos = pos.x;
	float yPos = pos.y;
	float zPos = pos.z;

	mat4 translateMat = mat4(
		1.0, 0.0, 0.0, xPos,
		0.0, 1.0, 0.0, yPos,
		0.0, 0.0, 1.0, zPos,
		0.0, 0.0, 0.0, 1.0
	);

	// return rotMat * transpose(scaleMat);
	return transpose(translateMat) * rotMat;
	// return transpose(translateMat) * rotMat * transpose(scaleMat);
	// return transpose(translateMat) * rotMat;
	// return transpose(translateMat) * transpose(scaleMat);
}
*/

void main() {

	// mat4 modelMat = getModelMatrix();
	// vec4 newPos = modelMat * vec4(aPos, 1.0);
	vec4 newPos = vec4(aPos, 1.0);
	// gl_Position = translate * scale * newPos;
	gl_Position = rot * newPos;

	color = aColor;
}