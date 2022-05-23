#pragma once

#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "renderer/texture.h"
#include "renderer/shaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "math/linAlgHelper.h"
#include "physics/boxCollider.h"
#include "input/input.h"
#include <math.h>
#include "transform.h"

class Arrow {
public:
	Arrow();
	Arrow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 color);
	void update();
	void render();

	Transform transform;
	BoxCollider boxCollider;

	bool clickedOn;

private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	ShaderProgram arrowShader;

	glm::vec3 color;
	glm::vec3 highlightColor;
};
