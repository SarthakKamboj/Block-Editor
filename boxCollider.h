#pragma once

#include "vec3.h"
#include "glm/glm.hpp"

typedef struct ray_t {
	glm::vec3 dir;
	glm::vec3 origin;
} ray_t;

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 dim, glm::vec3 scale, glm::vec3 trans);

	glm::vec3 dimensions;
	glm::vec3 scale;
	glm::vec3 transform;

	bool point_collide(glm::vec3& point);
	bool ray_collide(ray_t& point);

};
