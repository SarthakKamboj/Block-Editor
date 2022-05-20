#pragma once

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "lin_alg_helper.h"
#include "transform.h"
#include <string>
#include "texture.h"
#include "glm/gtc/type_ptr.hpp"

class DebugCube {
public:
	DebugCube();
	void render();

	Transform transform;
private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	ShaderProgram shader_program;

	void drawCube();
};
