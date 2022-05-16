#pragma once

#include "vec3.h"
#include "mat4.h"
#include "glm/glm.hpp"
#include "lin_alg_helper.h"

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 getViewMat();
	glm::vec3 pos, rot;
};
