#pragma once

#include "vao.h"
#include "vbo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "lin_alg_helper.h"
#include "boxCollider.h"
#include "input.h"

class Arrow {
public:
	Arrow();
	Arrow(glm::vec3 color);
	void update(glm::mat4& projection, glm::mat4& view);
	void render(glm::mat4& projection, glm::mat4& view);
	glm::vec3 pos, rot;

private:
	VAO vao;
	VBO vbo;
	ShaderProgram arrowShader;
	glm::vec3 scale;
	glm::vec3 color;
	glm::vec3 highlightColor;

	BoxCollider boxCollider;
};
