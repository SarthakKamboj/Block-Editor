#pragma once

#include "vao.h"
#include "vbo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "lin_alg_helper.h"
#include "boxCollider.h"
#include "input.h"

enum DIR {
	X, Y, Z
};

class Arrow {
public:
	Arrow();
	Arrow(glm::vec3 color, DIR dir);
	void update();
	void render();
	glm::vec3 pos, rot;

private:
	VAO vao;
	VBO vbo;
	ShaderProgram arrowShader;
	glm::vec3 scale;

	glm::vec3 color;
	glm::vec3 highlightColor;

	BoxCollider boxCollider;
	glm::vec3 colliderDim;
};
