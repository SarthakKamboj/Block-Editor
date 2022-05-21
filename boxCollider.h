#pragma once

#include "math/ray.h"
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderProgram.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "math/lin_alg_helper.h"
#include "transform.h"
#include <vector>

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

	Transform transform;

	ShaderProgram collider_program;

	bool point_collide(glm::vec3& point);
	bool ray_collide(Ray& point);
	Ray screen_to_local_ray(glm::vec2& screen_coords);
	glm::vec3 local_to_world(glm::vec3 point);

	VAO vao;
	VBO vbo;
	EBO ebo;

	void render();
	void set_color(glm::vec3 color);
	glm::vec3 color;

	glm::vec3 front_col_point;
	glm::vec3 back_col_point;
	glm::vec3 right_col_point;
	glm::vec3 left_col_point;
	glm::vec3 top_col_point;
	glm::vec3 bottom_col_point;

	std::vector<glm::vec3> local_col_points;

};
