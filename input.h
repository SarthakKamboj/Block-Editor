#pragma once

#include "SDL.h"

typedef struct mouse_click_state_t {
    bool left; 
    bool right;
} mouse_click_state_t;

typedef struct mouse_state_t {
    int x; 
    int y;
} mouse_state_t;

void handle_input(SDL_Event& event);
