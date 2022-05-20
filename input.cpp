#include "input.h"
#include <map>
#include "imgui_impl_sdl.h"

std::map<SDL_Keycode, bool> key_pressed_map;
SDL_Keycode keysToHandle[] = {
	SDLK_ESCAPE, SDLK_SPACE, SDL_QUIT, SDLK_o, SDLK_LCTRL,
	SDLK_w, SDLK_s, SDLK_d, SDLK_a
};

MouseClickState mouse_click_state;
MouseState mouse_state;
MouseWheel mouse_wheel;

void handle_input(SDL_Event& event) {
	for (auto const& keyEl : key_pressed_map) {
		key_pressed_map[keyEl.first] = false;
	}
	SDL_GetMouseState(&mouse_state.x, &mouse_state.y);
	mouse_click_state = {};
	mouse_wheel.y = 0;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT) {
			key_pressed_map[SDL_QUIT] = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			SDL_Keycode keyDown = event.key.keysym.sym;
			for (int i = 0; i < sizeof(keysToHandle) / sizeof(keysToHandle[0]); i++) {
				if (keysToHandle[i] == keyDown) {
					key_pressed_map[keyDown] = true;
					break;
				}
			}

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state.left = (event.button.button == SDL_BUTTON_LEFT);
			mouse_click_state.right = (event.button.button == SDL_BUTTON_RIGHT);
		}
		else if (event.type == SDL_MOUSEWHEEL) {
			std::cout << event.wheel.y << std::endl;
			mouse_wheel.y = event.wheel.y;
		}
	}
}

