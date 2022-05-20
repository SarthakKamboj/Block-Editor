#include "glad/glad.h"
#include "SDL.h"
#include <iostream>
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "cube.h"
#include "camera.h"
#include "input.h"
#include <map>
#include "cubeEditor.h"
#include "cameraEditor.h"
#include "arrow.h"
#include "grid.h"
#include "debugCube.h"
#include <fstream>
#include <chrono>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

extern std::map<SDL_Keycode, bool> key_pressed_map;
extern MouseClickState mouse_click_state;
extern MouseState mouse_state;

Camera* cam_ptr;
CubeEditor* cube_editor_ptr;
glm::mat4 projection(1.0f), view(1.0f);
float pov = 45.0f;

int width = 800, height = 800;
bool editor_hover;

std::vector<Cube> cubes;

void print_transform_to_file(std::ofstream& file, Transform transform) {
	file << "pos: " << transform.pos.x << ", " << transform.pos.y << ", " << transform.pos.z << "\n";
	file << "scale: " << transform.scale.x << ", " << transform.scale.y << ", " << transform.scale.z << "\n";
	file << "rot: " << transform.rot.x << ", " << transform.rot.y << ", " << transform.rot.z << "\n";
}

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

	editor_hover = false;

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
	glDepthFunc(GL_LESS);

	bool running = true;

	glm::vec3 clearColor(0.0f, 0.0f, 0.0f);

	CubeEditor cube_editor;
	cube_editor_ptr = &cube_editor;

	// Cube cubes[1];
	// Cube cubes[3];

	Cube cube0, cube1, cube2;
	cubes.push_back(cube0);
	cubes.push_back(cube1);
	cubes.push_back(cube2);

	cube_editor_ptr->cube = &cubes[0];
	cubes[1].transform.pos = glm::vec3(1.0f, 0.0f, 0.0f);
	cubes[2].transform.pos = glm::vec3(-1.0f, 0.0f, 0.0f);

	DebugCube debug_cube;

	Grid grid;

	Cube debugCube;
	debugCube.box_collider.set_color(glm::vec3(1.0f, 0.0f, 0.0f));

	uint32_t start = SDL_GetTicks();

	bool checked = false;
	bool show_demo_window = true;

	float val = 0.0f;

	projection = get_projection_matrix(pov, 0.1f, 100.0f, ((float)width) / height);

	Camera cam(0.0f, 0.0f, 10.0f);
	cam_ptr = &cam;

	CameraEditor camera_editor(&cam);

	int stencilBits;
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &stencilBits);
	std::cout << "stencilBits: " << stencilBits << std::endl;

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (running) {

		editor_hover = false;

		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		start = cur;

		SDL_Event event;

		view = cam.get_view_mat();

		handle_input(event);

		if (key_pressed_map[SDL_QUIT] || key_pressed_map[SDLK_ESCAPE]) {
			running = false;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGui::PushFont(robotoFont);

		editor_hover = ImGui::IsAnyItemHovered();

		if (mouse_click_state.left && !editor_hover && !key_pressed_map[SDLK_LCTRL]) {
			cube_editor.cube = NULL;
		}

		// for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].update();
		}

		// for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].late_update();
		}

		camera_editor.update();
		cube_editor.update();
		cam.update();
		grid.update();

		glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
		glClearStencil(0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

		cube_editor_ptr->setup_outline();
		// for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i].render();
		}
		grid.render();
		debug_cube.render();
		cube_editor_ptr->render();

		ImGui::Begin("issue window");
		if (ImGui::Button("log transforms")) {
			std::ofstream issue_file;
			issue_file.open("issues\\" + std::to_string(rand()) + ".txt");
			issue_file << "camera\n";
			issue_file << "------\n";
			print_transform_to_file(issue_file, cam.transform);
			for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
				issue_file << "\ncube " << i << "\n";
				print_transform_to_file(issue_file, cubes[i].transform);
			}
			issue_file.close();

		}
		ImGui::End();

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
