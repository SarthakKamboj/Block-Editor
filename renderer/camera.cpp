#include "camera.h"

extern MouseWheel mouseWheel;
extern glm::mat4 projection;
extern int width, height;
extern float pov;
extern std::map<SDL_Keycode, bool> keyPressedMap;
extern bool editorHover;

Camera::Camera() {
	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	// transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	// transform.rot = glm::vec3(0.0f, 50.0f, 20.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	lookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	startingLookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	startingPos = transform.pos;
	offset = startingPos - startingLookAtPos;
	offsetDist = pow(pow(offset.x, 2) + pow(offset.y, 2) + pow(offset.z, 2), 0.5f);
	offsetDist = 5;
}

Camera::Camera(float xPos, float yPos, float zPos) {
	transform.pos = glm::vec3(xPos, yPos, zPos);
	// transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	// transform.rot = glm::vec3(0.0f, 50.0f, 20.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	lookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	startingLookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	startingPos = transform.pos;
	offset = startingPos - startingLookAtPos;
	offsetDist = pow(pow(offset.x, 2) + pow(offset.y, 2) + pow(offset.z, 2), 0.5f);
	offsetDist = 5;
}

glm::vec3 Camera::offsetByAngle(float angle, Dir dir) {
	offsetDist = 1;
	float cosOffset = offsetDist * cos(0.0174533f * angle);
	float sinOffset = offsetDist * sin(0.0174533f * angle);

	if (dir == Dir::X) {
		return glm::vec3(0.0f, sinOffset, -cosOffset);
	}
	if (dir == Dir::Y) {
		// return glm::vec3(cosOffset, 0.0f, sinOffset);
		return glm::vec3(sinOffset, 0.0f, cosOffset);
	}
	return glm::vec3(cosOffset, -sinOffset, 0.0f);
}

void printVec3(glm::vec3& v) {
	std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
}

void Camera::updateLookAtPos() {
	// lookAtPos = transform.pos - offset;
	/*
	float xOffset1 = offsetDist * cos(0.0174533f * transform.rot.z);
	float yOffset1 = offsetDist * sin(0.0174533f * transform.rot.z);

	float zOffset1 = offsetDist * cos(0.0174533f * transform.rot.x);
	float yOffset2 = offsetDist * sin(0.0174533f * transform.rot.x);

	float xOffset2 = offsetDist * cos(0.0174533f * transform.rot.y);
	float zOffset2 = offsetDist * sin(0.0174533f * transform.rot.y);
	*/

	// float yOffset = offset.y * sin(transform.rot.z);
	// lookAtPos = transform.pos + glm::vec3(xOffset1 + xOffset2, yOffset1 + yOffset2, zOffset1 + zOffset2);
	// lookAtPos = transform.pos + glm::vec3(xOffset1, yOffset1, 0.0f);
	glm::vec3 xAngleOffset = offsetByAngle(transform.rot.x, Dir::X);
	glm::vec3 yAngleOffset = offsetByAngle(transform.rot.y, Dir::Y);
	glm::vec3 zAngleOffset = offsetByAngle(transform.rot.z, Dir::Z);

	// glm::vec3 xAngleOffset(0.0f, 0.0f, 0.0f);
	// glm::vec3 yAngleOffset(0.0f, 0.0f, 0.0f);
	// printVec3(xAngleOffset);
	// printVec3(yAngleOffset);
	// printVec3(zAngleOffset);
	// transform.
	// lookAtPos = glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0, 0.0f, 1.0f) * offsetDist;
	// lookAtPos = transform.pos - xAngleOffset - yAngleOffset - zAngleOffset;
	// lookAtPos = transform.pos - yAngleOffset;
	// lookAtPos = transform.pos - xAngleOffset;

	float yaw = transform.rot.y;
	float pitch = transform.rot.x;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	lookAtPos = transform.pos + direction;
}

void Camera::update() {
	float sensitivity = 5.0f;
	pov -= mouseWheel.y * sensitivity;
	pov = fmax(fmin(pov, 45.0f), 1.0f);
	if (mouseWheel.y > 0) {
		projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}
	else if (mouseWheel.y < 0) {
		projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}
	updateLookAtPos();
}

glm::mat4 Camera::getViewMat() {

	return glm::lookAt(transform.pos,
		lookAtPos,
		glm::vec3(0.0f, 1.0f, 0.0f));
}
