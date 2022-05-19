#pragma once

#include "vao.h"
#include "vbo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "lin_alg_helper.h"
#include "boxCollider.h"
#include "input.h"
#include <math.h>

typedef enum Dir {
	x, y, z
} Dir;

class Arrow {
public:
	Arrow();
	Arrow(glm::vec3 color, glm::vec3 rot, Dir dir);
	void update();
	void render();
	glm::vec3 pos, rot;

	void set_position(glm::vec3 _pos);
	glm::vec3 pos_offset;

private:
	VAO vao;
	VBO vbo;
	ShaderProgram arrow_shader;
	glm::vec3 scale;

	glm::vec3 color;
	glm::vec3 highlight_color;

	BoxCollider box_collider;
	glm::vec3 collider_dim;
};
