#pragma once

#include "glm/glm.hpp"
#include "math/linAlgHelper.h"
#include "transform.h"
#include "input/input.h"
#include <math.h>
#include <map>
#include "SDL.h"

typedef enum Dir {
	X, Y, Z
} Dir;

class Camera {
public:
	Camera();
	Camera(float xPos, float yPos, float zPos);
	glm::mat4 getViewMat();
	Transform transform;

	glm::vec3 lookAtPos;
	glm::vec3 startingLookAtPos;
	glm::vec3 startingPos;
	glm::vec3 offset;
	float offsetDist;

	void update();

private:
	void updateLookAtPos();
	glm::vec3 offsetByAngle(float angle, Dir dir);
};
