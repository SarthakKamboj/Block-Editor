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
	BoxCollider(glm::vec3 trans, glm::vec3 scale, glm::vec3 rot);

	glm::vec3 scale, rot;
	glm::vec3 transform;

	ShaderProgram colliderProgram;

	bool point_collide(glm::vec3& point);
	bool ray_collide(ray_t& point);
	ray_t screenToLocalRay(glm::vec2& screenCoords);

	VAO vao;
	VBO vbo;

	void render();
	void set_color(glm::vec3 color);
	glm::vec3 color;

};
