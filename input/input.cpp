#include "input.h"
#include <map>
#include "imgui_impl_sdl.h"

std::map<SDL_Keycode, bool> keyPressedMap;
std::map<SDL_Keycode, bool> keyDownMap;
SDL_Keycode keysToHandle[] = {
	SDLK_ESCAPE, SDLK_SPACE, SDL_QUIT, SDLK_o, SDLK_LCTRL,
	SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_h, SDLK_p, SDLK_l,
	SDLK_DELETE
};

MouseClickState mousePressedState;
MouseClickState mouseDownState;
MouseState mouseState;
MouseWheel mouseWheel;

extern int width, height;

glm::vec2 Input::screenToNdc(int screenX, int screenY) {
	float xNdc = ((float)(screenX - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenY - (height / 2.0f))) / (height / 2.0f);
	glm::vec2 ndc(xNdc, yNdc);
	return ndc;
}

void Input::handleInput() {
	SDL_Event event;
	for (auto const& keyEl : keyPressedMap) {
		keyPressedMap[keyEl.first] = false;
	}
	SDL_GetMouseState(&mouseState.x, &mouseState.y);
	mousePressedState = {};
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
					keyDownMap[keyDown] = true;
					break;
				}
			}
		}
						break;
		case SDL_KEYUP: {
			SDL_Keycode keyUp = event.key.keysym.sym;
			for (int i = 0; i < sizeof(keysToHandle) / sizeof(keysToHandle[0]); i++) {
				if (keysToHandle[i] == keyUp) {
					keyDownMap[keyUp] = false;
					break;
				}
			}
		}
					  break;
		case SDL_MOUSEBUTTONDOWN: {
			mousePressedState.left = (event.button.button == SDL_BUTTON_LEFT);
			mousePressedState.right = (event.button.button == SDL_BUTTON_RIGHT);

			if (mousePressedState.left) {
				mouseDownState.left = true;
			}
			if (mousePressedState.right) {
				mouseDownState.right = true;
			}
		}
								break;
		case SDL_MOUSEBUTTONUP: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mouseDownState.left = false;
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				mouseDownState.right = false;
			}
		}
							  break;
		case SDL_MOUSEWHEEL: {
			mouseWheel.y = event.wheel.y;
		}
						   break;

		}
	}
}

