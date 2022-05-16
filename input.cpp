#include "input.h"
#include <map>
#include "imgui_impl_sdl.h"

std::map<SDL_Keycode, bool> keyPressedMap;
SDL_Keycode keysToHandle[] = {
	SDLK_ESCAPE, SDLK_SPACE, SDL_QUIT, SDLK_o
};

mouse_click_state_t mouse_click_state;
mouse_state_t mouse_state;

void handle_input(SDL_Event& event) {
	for (auto const& keyEl : keyPressedMap) {
		keyPressedMap[keyEl.first] = false;
	}
	SDL_GetMouseState(&mouse_state.x, &mouse_state.y);
	mouse_click_state = {};
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT) {
			keyPressedMap[SDL_QUIT] = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			SDL_Keycode keyDown = event.key.keysym.sym;
			for (int i = 0; i < sizeof(keysToHandle) / sizeof(keysToHandle[0]); i++) {
				if (keysToHandle[i] == keyDown) {
					keyPressedMap[keyDown] = true;
					break;
				}
			}

		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			mouse_click_state.left = (event.button.button == SDL_BUTTON_LEFT);
			mouse_click_state.right = (event.button.button == SDL_BUTTON_RIGHT);

			/*
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouse_click_state.left = true;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				mouse_click_state.right = true;
			}
			*/

		}
	}
}

