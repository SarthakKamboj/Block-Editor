#pragma once

#include "vec3.h"
#include "mat4.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 getViewMat();
	// vec3 target, pos, offset;
	// vec3 rot;
	// glm::vec3 target, pos;
	glm::vec3 pos;
	// glm::vec3 offset;
	glm::vec3 rot;
};
