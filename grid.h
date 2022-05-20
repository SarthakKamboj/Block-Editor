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
#include "boxCollider.h"
#include "debugCube.h"
#include <math.h>

class Grid {
public:
	Grid();
	void update();
	void render();

	VAO vao;
	VBO vbo;
	EBO ebo;

	Transform transform;
	ShaderProgram shader_program;
	Texture texture;
	BoxCollider box_collider;
	DebugCube debug_cubes[6];

	int textureUnit;
};
