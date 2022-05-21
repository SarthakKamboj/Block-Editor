#pragma once

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "boxCollider.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"
#include "math/lin_alg_helper.h"
#include "camera.h"
#include "transform.h"
#include <string>
#include "texture.h"
#include "glm/gtc/type_ptr.hpp"
#include "debugCube.h"
#include <math.h>

class Cube {
public:
	Cube();

	void setup_render_outline();
	void render();
	void render_outline();

	void update();
	void late_update();

	Transform transform;

	glm::vec3 color;
	bool outline;

	static int idx;
	std::string name;

	BoxCollider box_collider;
private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	glm::vec3 outline_scale;

	ShaderProgram shader_program;
	ShaderProgram transparent_program;
	ShaderProgram outline_program;
	Texture texture;

	DebugCube debug_cubes[6];

	void drawCube();
};
