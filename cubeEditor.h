#pragma once

#include "cube.h"
#include "imgui.h"

#include "arrow.h"

class CubeEditor {
public:
	CubeEditor();
	void update();
	void render();

	Cube* cube;
	Arrow arrows[3];
};
