#pragma once

#include "SDL.h"

typedef struct MouseClickState {
	bool left;
	bool right;
} MouseClickState;

typedef struct MouseState {
	int x;
	int y;
} MouseState;

void handle_input(SDL_Event& event);
