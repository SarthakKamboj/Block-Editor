#include "window.h"

int width = 800, height = 800;

static bool first = true;
Window::Window() {
	window = SDL_CreateWindow("window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	context = SDL_GL_CreateContext(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ioPtr = &io;
	ImGui::StyleColorsDark();

	running = true;
	first = false;

}

void Window::initializeImGui() {
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Window::deInitializeImGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

static bool firstClose = true;
void Window::close() {
	/*
	if (firstClose) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
	*/

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::makeWindowCurrentContext() {
	SDL_GL_MakeCurrent(window, context);
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void Window::swapBuffers() {
	SDL_GL_SwapWindow(window);
}

void Window::updateDimension() {
	glViewport(0, 0, (int)ioPtr->DisplaySize.x, (int)ioPtr->DisplaySize.y);
}
