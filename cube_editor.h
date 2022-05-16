#pragma once

#include "cube.h"
#include "imgui.h"

class CubeEditor {
public:
	CubeEditor();
	void render();

	Cube* cube;
};
