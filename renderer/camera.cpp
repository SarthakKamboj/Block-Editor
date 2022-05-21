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
	transform.rot = glm::vec3(0.0f, 50.0f, 20.0f);
}

Camera::Camera(float xPos, float yPos, float zPos) {
	transform.pos = glm::vec3(xPos, yPos, zPos);
	// transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 50.0f, 20.0f);
}

void Camera::update() {
	if (editorHover) {
		return;
	}
	float sensitivity = 5.0f;
	pov -= mouseWheel.y * sensitivity;
	pov = fmax(fmin(pov, 60.0f), 45.0f);
	if (mouseWheel.y > 0) {
		projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}
	else if (mouseWheel.y < 0) {
		projection = getProjectionMatrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}

	float transformOffset = sensitivity * 0.1f;
	if (keyPressedMap[SDLK_w]) {
		transform.pos.z -= transformOffset;
	}
	else if (keyPressedMap[SDLK_s]) {
		transform.pos.z += transformOffset;
	}
	else if (keyPressedMap[SDLK_d]) {
		transform.pos.x += transformOffset;
	}
	else if (keyPressedMap[SDLK_a]) {
		transform.pos.x -= transformOffset;
	}
}

glm::mat4 Camera::getViewMat() {
	glm::vec3& pos = transform.pos;
	glm::mat4 posMat = getTranslationMatrix(-pos.x, -pos.y, -pos.z);
	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(-rot.x, -rot.y, -rot.z);
	return posMat * rotMat;
}
