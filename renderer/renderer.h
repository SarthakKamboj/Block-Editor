#pragma once

#include "shaderProgram.h"
#include "camera.h"
#include "../transform.h"
#include "glm/gtc/type_ptr.hpp"

class Renderer {
public:
	Renderer();
	void submitShader(ShaderProgram& shaderProgram, Transform transform);

	glm::mat4 projection;
	Camera camera;
};