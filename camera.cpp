#include "camera.h"

Camera::Camera() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(float xPos, float yPos, float zPos) {
	pos = glm::vec3(xPos, yPos, zPos);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::mat4 Camera::getViewMat() {
	glm::mat4 posMat = _getTranslationMatrix(-pos.x, -pos.y, -pos.z);
	glm::mat4 rotMat = _getRotMatrix(-rot.x, -rot.y, -rot.z);
	return posMat * rotMat;
}
