#pragma once

#include "camera.h"
#include "imgui.h"

class CameraEditor {
public:
	CameraEditor(Camera* camera);
	void render();

	Camera* cam;
};
