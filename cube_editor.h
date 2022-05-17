#pragma once

#include "cube.h"
#include "imgui.h"

#include "arrow.h"

class CubeEditor {
public:
	CubeEditor();
	void update(glm::mat4& projection, glm::mat4& view);
	void render(glm::mat4& projection, glm::mat4& view);

	Cube* cube;
	Arrow arrows[3];
};
