#pragma once

#include "glm/glm.hpp"

typedef struct NearFarPointsVec3 {
	glm::vec3 nearPoint;
	glm::vec3 farPoint;
} NearFarPointsVec3;

typedef struct NearFarPointsVec4 {
	glm::vec4 nearPoint;
	glm::vec4 farPoint;
} NearFarPointsVec4;
