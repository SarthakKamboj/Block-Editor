#include "camera.h"

extern MouseWheel mouseWheel;
extern glm::mat4 projection;
extern int width, height;
extern float pov;
extern std::map<SDL_Keycode, bool> keyPressedMap;
extern bool editorHover;

Camera::Camera() {
	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	lookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	offsetDist = 5;
}

Camera::Camera(float xPos, float yPos, float zPos) {
	transform.pos = glm::vec3(xPos, yPos, zPos);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	lookAtPos = glm::vec3(0.0f, 0.0f, 0.0f);
	offsetDist = 5;
}

void Camera::updateLookAtPos() {
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
