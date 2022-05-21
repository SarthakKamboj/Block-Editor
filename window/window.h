#pragma once

#include "SDL.h"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

class Window {
public:
	Window();

	bool running;
	SDL_Window* window;
	SDL_GLContext context;
	ImGuiIO* ioPtr;

	void swapBuffers();
	void makeWindowCurrentContext();
	void updateDimension();
	void close();
};