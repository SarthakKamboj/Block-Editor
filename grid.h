#pragma once

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "transform.h"
#include "shaderProgram.h"
#include "lin_alg_helper.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "texture.h"

class Grid {
public:
	Grid();
	void render();

	VAO vao;
	VBO vbo;
	EBO ebo;

	Transform transform;
	ShaderProgram shader_program;
	Texture texture;

	int textureUnit;
};
