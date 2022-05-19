#pragma once

#include "glm/glm.hpp"

class Transform {

public:
	Transform() {
		pos = glm::vec3(0.0f, 0.0f, 0.0f);
		rot = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale) {
		pos = _pos;
		rot = _rot;
		scale = _scale;
	}

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};
