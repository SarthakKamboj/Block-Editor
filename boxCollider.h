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
#include "transform.h"

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

	Transform transform;

	ShaderProgram collider_program;

	bool point_collide(glm::vec3& point);
	bool ray_collide(Ray& point);
	Ray screen_to_local_ray(glm::vec2& screen_coords);

	VAO vao;
	VBO vbo;

	void render();
	void set_color(glm::vec3 color);
	glm::vec3 color;

};
