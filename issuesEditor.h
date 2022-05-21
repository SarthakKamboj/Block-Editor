#pragma once

#include <fstream>
#include "imgui.h"
#include <string>
#include "renderer/camera.h"
#include "cube.h"
#include <vector>

class IssuesEditor {
public:
	static void Update(std::vector<Cube>& cubes, Camera& cam);
};
