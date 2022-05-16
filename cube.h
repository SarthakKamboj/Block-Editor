#pragma once

#include "vao.h"
#include "vbo.h"
#include "boxCollider.h"
// #include "vec3.h"
#include "mat4.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "lin_alg_helper.h"

class Cube {
public:
	Cube();
	void render(glm::mat4& projection, glm::mat4& view);

	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rot;

	glm::vec3 color;
	bool outline;

private:

	VAO vao;
	VBO vbo;

	glm::vec3 outlineScale;

	ShaderProgram shaderProgram;
	ShaderProgram outlineProgram;

	void drawCube();
};
