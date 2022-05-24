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
#include "glm/glm.hpp"
#include "renderer/line.h"
#include "nearFarPoints.h"
#include "helper/helper.h"
#include "groupSelector.h" 
#include "colorSelector.h"
#include "cubeManager.h"

extern std::map<SDL_Keycode, bool> keyPressedMap;
extern MouseClickState mousePressedState;
extern MouseState mouseState;
extern int width, height;
extern glm::mat4 projection, view;

Camera* camPtr;
CubeEditor* cubeEditorPtr;
ModeManager* modeManagerPtr;
Renderer* rendererPtr;
CameraEditor* cameraEditorPtr;
GroupSelector* groupSelectorPtr;
CubeManager* cubeManagerPtr;

bool editorHover;

float deltaTime;

bool debuggedOnce = false;
Transform debugCamTransform;

int Application::Init() {

	deltaTime = 0.0f;

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
	window.makeWindowCurrentContext();
	window.initializeImGui();

	Renderer renderer;
	rendererPtr = &renderer;

	CubeManager cubeManager;
	cubeManagerPtr = &cubeManager;

	CubeEditor cubeEditor;
	cubeEditorPtr = &cubeEditor;

	ModeManager modeManager;
	modeManagerPtr = &modeManager;

	Grid grid;

	uint32_t start = SDL_GetTicks();

	Camera cam(0.0f, 0.0f, -2.0f);
	camPtr = &cam;
	camPtr->transform.rot.y = -90.0f;

	ColorSelector colorSelector;

	CameraEditor cameraEditor(&cam);
	cameraEditorPtr = &cameraEditor;

	GroupSelector groupSelector;
	groupSelectorPtr = &groupSelector;

	DebugCube camPoint;
	camPoint.setColor(glm::vec3(0.0f, 1.0f, 1.0f));
	camPoint.transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	ImFont* robotoFont = window.ioPtr->Fonts->AddFontFromFileTTF("ext\\imgui\\fonts\\Roboto-Medium.ttf", 16.0f);

	while (window.running) {
		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		deltaTime = diff / 1000.0f;
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

		cubeEditor.cubeClickedOn = NULL;

		cubeManager.update();
		modeManager.update();
		cameraEditor.update();
		cubeEditor.update();
		grid.update();
		groupSelector.update();
		colorSelector.update();
		IssuesEditor::Update((Cube**)&cubeManager.cubes, cam);
		window.updateDimension();

		renderer.clear();
		cubeEditorPtr->setupOutline();
		cubeManager.render();

		grid.render();
		cubeEditorPtr->render();
		groupSelector.render();

		ImGui::Begin("debug mode");
		std::string modeStr = (renderer.isInDebugMode() ? "debug" : "regular");
		std::string modeStrFull = "mode: " + modeStr;
		ImGui::Text(modeStrFull.c_str());
		if (ImGui::Button("toggle debug mode")) {
			if (!renderer.isInDebugMode()) {
				camPoint.transform.pos = cameraEditorPtr->cam->transform.pos;
			}
			renderer.toggleDebugMode();
		}
		ImGui::End();

		if (renderer.isInDebugMode()) {
			camPoint.render();
		}

		ImGui::PopFont();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.swapBuffers();

	}

	return 0;
}