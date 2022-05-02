#include "camera.h"

Camera::Camera() {
	pos = vec3(0.0f, 0.0f, 0.0f);
	target = vec3(0.0f, 0.0f, 0.0f);
	offset = vec3_sub(target, pos);
}

Camera::Camera(float xPos, float yPos, float zPos) {
	pos = vec3(xPos, yPos, zPos);
	target = vec3(0.0f, 0.0f, 0.0f);
	offset = vec3_sub(target, pos);
}

mat4 Camera::getViewMat() {
	vec3 subDir = vec3_sub(pos, target);
	vec3 zAxis = vec3_normalize(subDir);
	vec3 upRough(0.0f, 1.0f, 0.0f);
	vec3 xAxis = vec3_normalize(vec3_cross(zAxis, upRough));
	vec3 yAxis = vec3_cross(xAxis, zAxis);

	mat4 projection(1.0f);
	projection.rows[0].coords.x = xAxis.coords.x;
	projection.rows[0].coords.y = xAxis.coords.y;
	projection.rows[0].coords.z = xAxis.coords.z;

	projection.rows[1].coords.x = yAxis.coords.x;
	projection.rows[1].coords.y = yAxis.coords.y;
	projection.rows[1].coords.z = yAxis.coords.z;

	projection.rows[2].coords.x = zAxis.coords.x;
	projection.rows[2].coords.y = zAxis.coords.y;
	projection.rows[2].coords.z = zAxis.coords.z;

	mat4 camPos = getTranslationMatrix(-pos.coords.x, -pos.coords.y, -pos.coords.z);
	mat4 camRot = getRotMatrix(-rot.coords.x, -rot.coords.y, -rot.coords.z);

	return mat4_multiply_mat4(projection, mat4_multiply_mat4(camPos, camRot));
}
