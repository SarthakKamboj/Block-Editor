#pragma once

#include "glm/glm.hpp"
#include "math/linAlgHelper.h"
#include "transform.h"
#include "input/input.h"
#include <math.h>
#include <map>
#include "SDL.h"

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 getViewMat();
	Transform transform;

	void update();
};
