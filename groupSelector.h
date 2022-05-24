#pragma once

#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "renderer/shaderProgram.h"
#include "glm/glm.hpp"
#include "math/ray.h"
#include <vector>
#include <cmath>

class GroupSelector {
public:
	GroupSelector();
	void update();
	void render();

	bool activelySelecting;
	glm::vec2 topLeftScreen, topRightScreen, bottomLeftScreen, bottomRightScreen;
private:
	void updateVertices();

	VAO vao;
	VBO vbo;
	EBO ebo;

	glm::vec2 topLeftNdc, topRightNdc, bottomLeftNdc, bottomRightNdc;
	ShaderProgram shaderProgram;
};