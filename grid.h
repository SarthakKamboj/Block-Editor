#pragma once

#include "vao.h"
#include "vbo.h"
#include "transform.h"
#include "shaderProgram.h"
#include "lin_alg_helper.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Grid {
public:
	Grid();
	void render();

	VAO vao;
	VBO vbo;

	Transform transform;
	ShaderProgram shader_program;

	unsigned int texture;
	unsigned char* data;
};
