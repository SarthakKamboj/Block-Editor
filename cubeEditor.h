#pragma once

#include "cube.h"
#include "imgui.h"
#include "transform.h"
#include "arrow.h"
#include <vector>

class CubeEditor {
public:
	CubeEditor();
	void setupOutline();
	void update();
	void render();

	Transform transform;
	Arrow xArrow, yArrow, zArrow;
	Cube* cube;
	Arrow arrows[3];
};
