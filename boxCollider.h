#pragma once

#include "vec3.h"
#include "glm/glm.hpp"

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 dim, glm::vec3 scale, glm::vec3 trans);

	glm::vec3 dimensions;
	glm::vec3 scale;
	glm::vec3 transform;

	bool point_collide(glm::vec3& point);

};
