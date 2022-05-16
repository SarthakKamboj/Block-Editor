#pragma once

#include "cube.h"
#include "imgui.h"

class CubeEditor {
public:
	CubeEditor();
	void update();

	Cube* cube;
};
