#pragma once

#include "glm/glm.hpp"
#include "lin_alg_helper.h"
#include "transform.h"

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 get_view_mat();
	// glm::vec3 pos, rot;
	Transform transform;
};
