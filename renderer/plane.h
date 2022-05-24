#pragma once

#include "renderer/shaderProgram.h"
#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "transform.h"

class Plane {
public:
	Plane();
	void render();
	Transform transform;

private:
	ShaderProgram shaderProgram;
	VAO vao;
	VBO vbo;
	EBO ebo;
};
