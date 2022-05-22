#pragma once

#include "vao.h"
#include "vbo.h"
#include "shaderProgram.h"
#include "glm/glm.hpp"

class Line {
public:
	float vertices[6];
	Line();
	void render();
	void setStartPos(glm::vec3 _pos);
	void setEndPos(glm::vec3 _pos);

	VAO vao;
	VBO vbo;
	ShaderProgram lineProgram;
};