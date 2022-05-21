#pragma once

#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "transform.h"
#include "renderer/shaderProgram.h"
#include "math/linAlgHelper.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "renderer/texture.h"
#include "physics/boxCollider.h"
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
	ShaderProgram shaderProgram;
	Texture texture;
	BoxCollider boxCollider;
	DebugCube debugCubes[6];

	int textureUnit;
};
