#pragma once

#include "SDL.h"
#include <iostream>

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

void handle_input(SDL_Event& event);
