#pragma once

#include "vao.h"
#include "vbo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "lin_alg_helper.h"

class Arrow {
public:
	Arrow(glm::vec3 color);
	void render(glm::mat4& projection, glm::mat4& view);
	glm::vec3 rot;

private:
	VAO vao;
	VBO vbo;
	ShaderProgram arrowShader;
	glm::vec3 pos, scale;
	glm::vec3 color;
};
