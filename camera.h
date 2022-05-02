#pragma once

#include "vec3.h"
#include "mat4.h"

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	mat4 getViewMat();
	vec3 target, pos, offset;
};
