#include "camera.h"

extern MouseWheel mouse_wheel;
extern glm::mat4 projection;
extern int width, height;
extern float pov;
extern std::map<SDL_Keycode, bool> key_pressed_map;
extern bool editor_hover;

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
	if (editor_hover) {
		return;
	}
	float sensitivity = 5.0f;
	pov -= mouse_wheel.y * sensitivity;
	pov = fmax(fmin(pov, 60.0f), 45.0f);
	if (mouse_wheel.y > 0) {
		projection = get_projection_matrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}
	else if (mouse_wheel.y < 0) {
		projection = get_projection_matrix(pov, 0.1f, 100.0f, ((float)width) / height);
	}

	float transformOffset = sensitivity * 0.1f;
	if (key_pressed_map[SDLK_w]) {
		transform.pos.z -= transformOffset;
	}
	else if (key_pressed_map[SDLK_s]) {
		transform.pos.z += transformOffset;
	}
	else if (key_pressed_map[SDLK_d]) {
		transform.pos.x += transformOffset;
	}
	else if (key_pressed_map[SDLK_a]) {
		transform.pos.x -= transformOffset;
	}
}

glm::mat4 Camera::get_view_mat() {
	glm::vec3& pos = transform.pos;
	glm::mat4 posMat = get_translation_matrix(-pos.x, -pos.y, -pos.z);
	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = get_rotation_matrix(-rot.x, -rot.y, -rot.z);
	return posMat * rotMat;
}
