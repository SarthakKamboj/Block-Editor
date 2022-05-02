#include "camera.h"

Camera::Camera() {
	pos = vec3(0.0f, 0.0f, 0.0f);
	lookAt = vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(float xPos, float yPos, float zPos) {
	pos = vec3(xPos, yPos, zPos);
	lookAt = vec3(0.0f, 0.0f, 0.0f);
}

mat4 Camera::getViewMat() {
	vec3 subDir = sub(pos, lookAt);
	vec3 lookAtDir = normalize(subDir);
	vec3 upRough(0.0f, 1.0f, 0.0f);
	vec3 side = cross(upRough, lookAtDir);
	vec3 up = cross(lookAtDir, side);

	mat4 projection(1.0f);
	projection.rows[0].vals[0] = side.coords.x;
	projection.rows[0].vals[1] = up.coords.x;
	projection.rows[0].vals[2] = -lookAtDir.coords.x;
	projection.rows[0].vals[3] = 0.0f;

	projection.rows[1].vals[0] = side.coords.y;
	projection.rows[1].vals[1] = up.coords.y;
	projection.rows[1].vals[2] = -lookAtDir.coords.y;
	projection.rows[1].vals[3] = 0.0f;

	projection.rows[2].vals[0] = side.coords.z;
	projection.rows[2].vals[1] = up.coords.z;
	projection.rows[2].vals[2] = -lookAtDir.coords.z;
	projection.rows[2].vals[3] = 0.0f;

	mat4 camPos = getTranslationMatrix(-pos.coords.x, -pos.coords.y, -pos.coords.z);

	return mat4_multiply_mat4(camPos, projection);
}
