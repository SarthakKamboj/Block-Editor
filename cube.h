#pragma once

#include "vao.h"
#include "vbo.h"

class Cube {
public:
	Cube();
	void render();

private:
	VAO vao;
	VBO vbo;
};
