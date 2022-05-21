#pragma once

#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "physics/boxCollider.h"
#include "renderer/shaderProgram.h"
#include "glm/glm.hpp"
#include "math/linAlgHelper.h"
#include "renderer/camera.h"
#include "transform.h"
#include <string>
#include "renderer/texture.h"
#include "glm/gtc/type_ptr.hpp"
#include "debugCube.h"
#include <math.h>

class Cube {
public:
	Cube();

	void setupRenderOutline();
	void render();
	void renderOutline();

	void update();
	void lateUpdate();

	Transform transform;

	glm::vec3 color;
	bool outline;

	static int idx;
	std::string name;

	BoxCollider boxCollider;
private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	glm::vec3 outlineScale;

	ShaderProgram shaderProgram;
	ShaderProgram transparentProgram;
	ShaderProgram outlineProgram;
	Texture texture;

	DebugCube debugCubes[6];

	void drawCube();
};
