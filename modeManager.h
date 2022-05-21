#pragma once

#include "imgui.h"
#include <string>

typedef enum Mode {
	ADD, SELECT
} Mode;

class ModeManager {
public:
	ModeManager();
	void update();

	Mode mode;
	std::string modeString;
};
