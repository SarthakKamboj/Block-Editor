#include "input.h"
#include <map>
#include "imgui_impl_sdl.h"

std::map<SDL_Keycode, bool> keyPressedMap;
SDL_Keycode keysToHandle[] = {
	SDLK_ESCAPE, SDLK_SPACE, SDL_QUIT, SDLK_o, SDLK_LCTRL,
	SDLK_w, SDLK_s, SDLK_d, SDLK_a
};

MouseClickState mouseClickState;
MouseState mouseState;
MouseWheel mouseWheel;

void handleInput(SDL_Event& event) {
	for (auto const& keyEl : keyPressedMap) {
		keyPressedMap[keyEl.first] = false;
	}
	SDL_GetMouseState(&mouseState.x, &mouseState.y);
	mouseClickState = {};
	mouseWheel.y = 0;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type) {
		case SDL_QUIT: {
			keyPressedMap[SDL_QUIT] = true;
		}
					 break;
		case SDL_KEYDOWN: {
			SDL_Keycode keyDown = event.key.keysym.sym;
			for (int i = 0; i < sizeof(keysToHandle) / sizeof(keysToHandle[0]); i++) {
				if (keysToHandle[i] == keyDown) {
					keyPressedMap[keyDown] = true;
					break;
				}
			}
		}
						break;
		case SDL_MOUSEBUTTONDOWN: {
			mouseClickState.left = (event.button.button == SDL_BUTTON_LEFT);
			mouseClickState.right = (event.button.button == SDL_BUTTON_RIGHT);
		}
								break;
		case SDL_MOUSEWHEEL: {
			mouseWheel.y = event.wheel.y;
		}
						   break;

		}
	}
}

