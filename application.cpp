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

extern std::map<SDL_Keycode, bool> keyPressedMap;
extern MouseClickState mouseClickState;
extern MouseState mouseState;
extern int width, height;
extern glm::mat4 projection, view;

Camera* camPtr;
CubeEditor* cubeEditorPtr;
ModeManager* modeManagerPtr;
Renderer* rendererPtr;
CameraEditor* cameraEditorPtr;

bool editorHover;

std::vector<Cube> cubes;
float deltaTime;

bool debuggedOnce = false;
Transform debugCamTransform;

NearFarPointsVec3 screenToWorld(glm::vec2 screenCoords) {
	float xNdc = ((float)(screenCoords.x - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenCoords.y - (height / 2.0f))) / (height / 2.0f);
	glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
	glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

	glm::mat4 screenToWorldMat = glm::inverse(projection * view);
	glm::vec4 nearCoord = screenToWorldMat * nearNdc;
	glm::vec4 farCoord = screenToWorldMat * farNdc;

	nearCoord /= nearCoord.w;
	farCoord /= farCoord.w;

	glm::vec3 nearVec3(nearCoord.x, nearCoord.y, nearCoord.z);
	glm::vec3 farVec3(farCoord.x, farCoord.y, farCoord.z);

	NearFarPointsVec3 nearFarPoints;
	nearFarPoints.nearPoint = nearVec3;
	nearFarPoints.farPoint = farVec3;

	return nearFarPoints;
}

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

	CubeEditor cubeEditor;
	cubeEditorPtr = &cubeEditor;

	Cube cube0;
	cubes.push_back(cube0);

	cubeEditorPtr->cube = &cubes[0];
	cubes[0].transform.pos = glm::vec3(0.0f, 0.5f, -8.0f);
	cubes[0].transform.scale = glm::vec3(1.25f, 1.5f, 2.0f);

	ModeManager modeManager;
	modeManagerPtr = &modeManager;

	Grid grid;

	uint32_t start = SDL_GetTicks();

	Camera cam(0.0f, 0.0f, -2.0f);
	camPtr = &cam;

	CameraEditor cameraEditor(&cam);
	cameraEditorPtr = &cameraEditor;

	DebugCube camPoint;
	camPoint.setColor(glm::vec3(0.0f, 1.0f, 1.0f));
	camPoint.transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	DebugCube clickColPoints[6];
	for (int i = 0; i < 6; i++) {
		clickColPoints[i].setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		clickColPoints[i].transform.scale = glm::vec3(0.05f, 0.05f, 0.05f);
	}

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
		grid.update();
		IssuesEditor::Update(cubes, cam);
		window.updateDimension();

		renderer.clear();
		cubeEditorPtr->setupOutline();
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].render();
		}
		grid.render();
		cubeEditorPtr->render();

		ImGui::Begin("debug mode");
		std::string modeStr = (renderer.isInDebugMode() ? "debug" : "regular");
		std::string modeStrFull = "mode: " + modeStr;
		ImGui::Text(modeStrFull.c_str());
		if (ImGui::Button("toggle debug mode")) {
			renderer.toggleDebugMode();
			Camera* prevCamera = cameraEditor.cam;
			if (renderer.isInDebugMode()) {
				camPoint.transform.pos = prevCamera->transform.pos;
			}
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