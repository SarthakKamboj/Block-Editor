#pragma once

#include "shaderProgram.h"
#include "camera.h"
#include "../transform.h"
#include "glm/gtc/type_ptr.hpp"
#include "transform.h"
#include "helper/helper.h"

class Renderer {
public:
	Renderer();
	void submitShader(ShaderProgram& shaderProgram, Transform transform);
	void submitShaderWithoutTransform(ShaderProgram& shaderProgram);
	void frameSetup();
	void clear();
	void enableDebugMode();
	void disableDebugMode();
	void toggleDebugMode();
	bool isInDebugMode();

private:
	bool debugMode;
	Camera debugCamera;
	Camera* prevCamera;
	Transform prevDebugCamTransform;

};
