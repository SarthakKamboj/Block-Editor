#include "camera.h"

Camera::Camera() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(float xPos, float yPos, float zPos) {
	pos = glm::vec3(xPos, yPos, zPos);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::mat4 Camera::get_view_mat() {
	glm::mat4 posMat = get_translation_matrix(-pos.x, -pos.y, -pos.z);
	glm::mat4 rotMat = get_rotation_matrix(-rot.x, -rot.y, -rot.z);
	return posMat * rotMat;
}
