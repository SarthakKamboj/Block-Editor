#pragma once

#include "glm/glm.hpp"

typedef struct ray_t {
	glm::vec3 dir;
	glm::vec3 origin;
} ray_t;
