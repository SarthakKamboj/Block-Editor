#include "input.h"
#include <map>
#include "imgui_impl_sdl.h"

std::map<SDL_Keycode, bool> keyPressedMap;
SDL_Keycode keysToHandle[] = {
    SDLK_ESCAPE, SDLK_SPACE, SDL_QUIT
};

void handle_input(SDL_Event& event) {
    for (auto const& keyEl : keyPressedMap) {
        keyPressedMap[keyEl.first] = false;
    }
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
    }
}

