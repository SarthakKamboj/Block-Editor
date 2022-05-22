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
bool debugMode;

bool debuggedOnce = false;
Transform debugCamTransform;

typedef struct NearFarPoints {
	glm::vec3 nearPoint;
	glm::vec3 farPoint;
} NearFarPoints;

NearFarPoints screenToWorld(glm::vec2 screenCoords) {
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

	NearFarPoints nearFarPoints;
	nearFarPoints.nearPoint = nearVec3;
	nearFarPoints.farPoint = farVec3;

	return nearFarPoints;
}

int Application::Init() {

	debugMode = false;

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

	Line collisionLine;

	Cube cube0, cube1, cube2;
	cubes.push_back(cube0);
	cubes.push_back(cube1);
	cubes.push_back(cube2);

	cubeEditorPtr->cube = &cubes[0];
	cubes[0].transform.pos = glm::vec3(0.0f, 0.0f, -5.0f);
	cubes[1].transform.pos = glm::vec3(1.0f, 0.0f, -5.0f);
	cubes[2].transform.pos = glm::vec3(-1.0f, 0.0f, -5.0f);

	DebugCube debugCube;
	ModeManager modeManager;
	modeManagerPtr = &modeManager;

	Grid grid;

	uint32_t start = SDL_GetTicks();

	// Camera cam(0.0f, 0.0f, 10.0f);
	Camera cam(0.0f, 0.0f, 0.0f);
	// Camera cam(0.0f, 5.0f, 10.0f);
	camPtr = &cam;

	Camera debugCamera;

	CameraEditor cameraEditor(&cam);
	cameraEditorPtr = &cameraEditor;

	// int stencilBits;
	// glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencilBits);
	// std::cout << "stencilBits: " << stencilBits << std::endl;

	BoxCollider camPoint;
	camPoint.setColor(glm::vec3(1.0f, 0.0f, 0.0f));

	BoxCollider lineColPoints[6];
	for (int i = 0; i < 6; i++) {
		lineColPoints[i].setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		lineColPoints[i].transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
	}

	BoxCollider nearPoint, farPoint;
	nearPoint.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	farPoint.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	nearPoint.transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
	farPoint.transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	ImFont* robotoFont = window.ioPtr->Fonts->AddFontFromFileTTF("ext\\imgui\\fonts\\Roboto-Medium.ttf", 16.0f);
	bool clicked = false;

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
		if (!debugMode) {
			cam.update();
		}
		else {
			debugCamera.update();
		}
		grid.update();
		IssuesEditor::Update(cubes, cam);
		if (debugMode) {
			debugCamTransform = debugCamera.transform;

			std::vector<glm::vec3>& colPoints = cubeEditorPtr->arrows[1].boxCollider.localColPoints;
			for (int i = 0; i < colPoints.size(); i++) {
				lineColPoints[i].transform.pos = colPoints[i];
			}
		}

		renderer.clear();
		window.updateDimension();

		cubeEditorPtr->setupOutline();
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].render();
		}
		grid.render();
		cubeEditorPtr->render();
		if (debugMode) {
			camPoint.render();
			std::vector<glm::vec3>& colPoints = cubeEditorPtr->arrows[1].boxCollider.localColPoints;
			glDisable(GL_DEPTH_TEST);
			for (int i = 0; i < colPoints.size(); i++) {
				lineColPoints[i].render();
			}
			glEnable(GL_DEPTH_TEST);
		}
		collisionLine.render();
		if (clicked) {
			// nearPoint.render();
			// farPoint.render();
			// collisionLine.render();
		}

		ImGui::Begin("debug mode");
		std::string modeStr = (debugMode ? "debug" : "regular");
		std::string modeStrFull = "mode: " + modeStr;
		ImGui::Text(modeStrFull.c_str());
		if (ImGui::Button("toggle debug mode")) {
			debugMode = !debugMode;
			if (debugMode) {
				cameraEditor.cam = &debugCamera;
				camPoint.transform = cam.transform;
				if (!debuggedOnce) {
					debugCamera.transform = cam.transform;
					debugCamTransform = cam.transform;
					debuggedOnce = true;
				}
				else {
					debugCamera.transform = debugCamTransform;
				}
				camPoint.transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
			}
			else {
				cameraEditor.cam = &cam;
			}
		}
		ImGui::End();

		ImGui::PopFont();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (mouseClickState.left && !debugMode && !editorHover) {
			glm::vec2 screenCoords(mouseState.x, mouseState.y);
			NearFarPoints nearFarPoints = screenToWorld(screenCoords);
			nearPoint.transform.pos = nearFarPoints.nearPoint;
			farPoint.transform.pos = nearFarPoints.farPoint;
			clicked = true;
			collisionLine.setStartPos(nearPoint.transform.pos);
			collisionLine.setEndPos(farPoint.transform.pos);
		}

		window.swapBuffers();

	}

	return 0;
}