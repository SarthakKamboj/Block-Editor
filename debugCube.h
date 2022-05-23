#pragma once

#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "renderer/shaderProgram.h"
#include "glm/glm.hpp"
#include "math/linAlgHelper.h"
#include "transform.h"
#include <string>
#include "renderer/texture.h"
#include "glm/gtc/type_ptr.hpp"

class DebugCube {
public:
	DebugCube();
	void render();
	void setColor(glm::vec3 color);

	Transform transform;
private:
	VAO vao;
	VBO vbo;
	EBO ebo;

	ShaderProgram shaderProgram;

	void drawCube();
};
