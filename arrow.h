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
#include "transform.h"

class Arrow {
public:
	Arrow();
	Arrow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 color);
	void update();
	void render();

	Transform transform;

private:
	VAO vao;
	VBO vbo;
	ShaderProgram arrow_shader;

	glm::vec3 color;
	glm::vec3 highlight_color;

	BoxCollider box_collider;
	glm::vec3 collider_dim;
};
