#include "camera.h"

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

glm::mat4 Camera::get_view_mat() {
	glm::vec3& pos = transform.pos;
	glm::mat4 posMat = get_translation_matrix(-pos.x, -pos.y, -pos.z);
	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = get_rotation_matrix(-rot.x, -rot.y, -rot.z);
	return posMat * rotMat;
}
