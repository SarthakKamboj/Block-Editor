#pragma once

#include "cube.h"
#include "imgui.h"
#include "transform.h"
#include "arrow.h"

class CubeEditor {
public:
	CubeEditor();
	void setup_outline();
	void update();
	void render();

	Transform transform;
	Arrow x_arrow, y_arrow, z_arrow;
	Cube* cube;
	Arrow arrows[3];
};
