#pragma once

#include "glm/glm.hpp"
#include "lin_alg_helper.h"

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 getViewMat();
	glm::vec3 pos, rot;
};
