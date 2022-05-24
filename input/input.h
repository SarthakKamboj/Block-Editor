#pragma once

#include "SDL.h"
#include <iostream>
#include "glm/glm.hpp"

typedef struct MouseClickState {
	bool left;
	bool right;
} MouseClickState;

typedef struct MouseState {
	int x;
	int y;
} MouseState;

typedef struct MouseWheel {
	int y;
} MouseWheel;

namespace Input {
	void handleInput();
	glm::vec2 screenToNdc(int screenX, int screenY);
}
