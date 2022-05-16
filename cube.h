#pragma once

#include "vao.h"
#include "vbo.h"
#include "boxCollider.h"
#include "mat4.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "lin_alg_helper.h"
#include "camera.h"
#include <string>

class Cube {
public:
	Cube();
	void setup_render_outline(glm::mat4& projection, glm::mat4& view);
	void render(glm::mat4& projection, glm::mat4& view);
	void render_outline();

	void update(Camera& camera);
	void late_update();

	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rot;

	glm::vec3 color;
	bool outline;

	static int idx;
	std::string name;
private:


	VAO vao;
	VBO vbo;

	glm::vec3 outlineScale;

	BoxCollider boxCollider;

	ShaderProgram shaderProgram;
	ShaderProgram transparentProgram;
	ShaderProgram outlineProgram;

	void drawCube();
};
