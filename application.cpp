#include "glad/glad.h"
#include "SDL.h"
#include <iostream>
#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "renderer/shaderProgram.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "cube.h"
#include "renderer/camera.h"
#include "input/input.h"
#include <map>
#include "cubeEditor.h"
#include "cameraEditor.h"
#include "arrow.h"
#include "grid.h"
#include "debugCube.h"
#include <fstream>
#include <string>
#include <vector>
#include "modeManager.h"
#include "window/window.h"
#include "application.h"
#include "renderer/renderer.h"
#include "issuesEditor.h"

extern std::map<SDL_Keycode, bool> keyPressedMap;
extern MouseClickState mouseClickState;
extern MouseState mouseState;

Camera* camPtr;
CubeEditor* cubeEditorPtr;
ModeManager* modeManagerPtr;
Renderer* rendererPtr;

bool editorHover;

std::vector<Cube> cubes;

int Application::Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "sdl gave error" << std::endl;
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	editorHover = false;

	Window window;
	Renderer renderer;
	rendererPtr = &renderer;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	CubeEditor cubeEditor;
	cubeEditorPtr = &cubeEditor;

	Cube cube0, cube1, cube2;
	cubes.push_back(cube0);
	cubes.push_back(cube1);
	cubes.push_back(cube2);

	cubeEditorPtr->cube = &cubes[0];
	cubes[1].transform.pos = glm::vec3(1.0f, 0.0f, 0.0f);
	cubes[2].transform.pos = glm::vec3(-1.0f, 0.0f, 0.0f);

	DebugCube debugCube;
	ModeManager modeManager;
	modeManagerPtr = &modeManager;

	Grid grid;

	uint32_t start = SDL_GetTicks();

	Camera cam(0.0f, 0.0f, 10.0f);
	camPtr = &cam;

	CameraEditor cameraEditor(&cam);

	int stencilBits;
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencilBits);
	std::cout << "stencilBits: " << stencilBits << std::endl;

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	ImFont* robotoFont = window.ioPtr->Fonts->AddFontFromFileTTF("ext\\imgui\\fonts\\Roboto-Medium.ttf", 16.0f);

	while (window.running) {

		editorHover = false;

		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		start = cur;

		Input::handleInput();

		if (keyPressedMap[SDL_QUIT] || keyPressedMap[SDLK_ESCAPE]) {
			window.running = false;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		renderer.frameSetup();

		ImGui::PushFont(robotoFont);

		editorHover = ImGui::IsAnyItemHovered();

		if ((mouseClickState.left && !editorHover && !keyPressedMap[SDLK_LCTRL]) || (modeManager.mode != Mode::SELECT)) {
			cubeEditor.cube = NULL;
		}

		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].update();
		}

		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].lateUpdate();
		}

		modeManager.update();
		cameraEditor.update();
		cubeEditor.update();
		cam.update();
		grid.update();

		IssuesEditor::Update(cubes, cam);

		renderer.clear();
		window.updateDimension();

		cubeEditorPtr->setupOutline();
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].render();
		}
		grid.render();
		cubeEditorPtr->render();

		ImGui::PopFont();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.swap();

	}

	window.close();
	return 0;
}