#pragma once

#include "renderer/camera.h"
#include "imgui.h"

class CameraEditor {
public:
	CameraEditor(Camera* camera);
	void update();

	Camera* cam;
};
