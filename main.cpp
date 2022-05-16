#include "glad/glad.h"
#include "SDL.h"
#include <iostream>
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"
#include "mat4.h"
#include "vec3.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "cube.h"
#include "camera.h"
#include "input.h"
#include <map>
#include "cube_editor.h"

extern std::map<SDL_Keycode, bool> keyPressedMap;
extern mouse_click_state_t mouse_click_state;
extern mouse_state_t mouse_state;

CubeEditor* cubeEditorPtr;

int width = 800, height = 800;

int main(int argc, char* args[]) {

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


	SDL_Window* window = SDL_CreateWindow("window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImFont* robotoFont = io.Fonts->AddFontFromFileTTF("ext\\imgui\\fonts\\Roboto-Medium.ttf", 16.0f);

	ImGui_ImplSDL2_InitForOpenGL(window, context);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CCW);

	bool running = true;

	vec3 clearColor(0.0f, 0.0f, 0.0f);

	CubeEditor cubeEditor;
	cubeEditorPtr = &cubeEditor;

	Cube cubes[3];

	uint32_t start = SDL_GetTicks();

	bool checked = false;
	bool show_demo_window = true;

	float val = 0.0f;

	glm::mat4 projection = _getProjectionMat(45.0f, 0.1f, 100.0f, ((float)width) / height);

	Camera cam(0.0f, 0.0f, 5.0f);

	int stencilBits;
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencilBits);
	std::cout << "stencilBits: " << stencilBits << std::endl;

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (running) {

		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		start = cur;

		SDL_Event event;

		glm::mat4 view = cam.getViewMat();

		handle_input(event);

		for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
			cubes[i].update(cam);
		}

		for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
			cubes[i].late_update();
		}

		if (keyPressedMap[SDL_QUIT] || keyPressedMap[SDLK_ESCAPE]) {
			running = false;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		glClearColor(clearColor.coords.x, clearColor.coords.y, clearColor.coords.z, 1.0f);
		glClearStencil(0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

		for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
			cubes[i].render(projection, view);
		}

		ImGui::PushFont(robotoFont);

		cubeEditor.render();

		{
			ImGui::Begin("Camera Info");

			if (ImGui::CollapsingHeader("transform")) {
				if (ImGui::TreeNode("position")) {
					ImGui::SliderFloat("x", &cam.pos.x, -10.0f, 10.0f);
					ImGui::SliderFloat("y", &cam.pos.y, -10.0f, 10.0f);
					ImGui::SliderFloat("z", &cam.pos.z, -10.0f, 10.0f);

					if (ImGui::Button("reset")) {
						cam.pos = glm::vec3(0.0f, 0.0f, 5.0f);
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("rotation")) {
					ImGui::SliderFloat("x", &cam.rot.x, -180.0f, 180.0f);
					ImGui::SliderFloat("y", &cam.rot.y, -180.0f, 180.0f);
					ImGui::SliderFloat("z", &cam.rot.z, -180.0f, 180.0f);
					if (ImGui::Button("reset")) {
						cam.rot = glm::vec3();
					}
					ImGui::TreePop();
				}
			}

			ImGui::End();
		}

		ImGui::PopFont();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(window);

	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
