#pragma once

#include "ray.h"
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderProgram.h"
#include "vao.h"
#include "vbo.h"
#include "lin_alg_helper.h"

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 dim, glm::vec3 scale, glm::vec3 trans);

	glm::vec3 dimensions;
	glm::vec3 scale;
	glm::vec3 transform;

	ShaderProgram colliderProgram;

	bool point_collide(glm::vec3& point);
	bool ray_collide(ray_t& point);

	VAO vao;
	VBO vbo;

	void render();

};
