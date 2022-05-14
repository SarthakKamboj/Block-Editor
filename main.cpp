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

extern std::map<SDL_Keycode, bool> keyPressedMap;

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "sdl gave error" << std::endl;
		return -1;
	}

	std::cout << "sdl works" << std::endl;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	int width = 800, height = 800;

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
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CCW);

	bool running = true;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	Cube cube;

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	ShaderProgram shaderProgram(vertexFilePath, fragmentFilePath);

	shaderProgram.setFloat("windowHeight", (float)height);

	vec3 pos;
	vec3 scale(1.0f, 1.0f, 1.0f);
	vec3 rot;

	float posDelta = 0.01f;
	float scaleDelta = 0.1f;
	float rotDelta = 1.0f;

	uint32_t start = SDL_GetTicks();

	bool checked = false;
	bool show_demo_window = true;

	float val = 0.0f;

	vec3 triangleColor(1.0f, 0.0f, 1.0f);

	mat4 projection = getProjectionMat(45.0f, 0.1f, 100.0f, ((float)width) / height);

	Camera cam(0.0f, 0.0f, 5.0f);

	while (running) {

		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		start = cur;

		SDL_Event event;

		mat4 view = cam.getViewMat();
        
        handle_input(event);

        if (keyPressedMap[SDL_QUIT] || keyPressedMap[SDLK_ESCAPE]) {
            running = false;
        }

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		glClearColor(r, g, b, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

		shaderProgram.bind();

		mat4 translationMat = getTranslationMatrix(pos.coords.x, pos.coords.y, pos.coords.z);
		shaderProgram.setMat4("translate", GL_TRUE, mat4_get_ptr(translationMat));

		mat4 rotMat = getRotMatrix(rot.coords.x, rot.coords.y, rot.coords.z);
		shaderProgram.setMat4("rot", GL_TRUE, mat4_get_ptr(rotMat));

		mat4 scaleMat = getScaleMatrix(scale.coords.x, scale.coords.y, scale.coords.z);
		shaderProgram.setMat4("scale", GL_TRUE, mat4_get_ptr(scaleMat));

		shaderProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));

		shaderProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));
		shaderProgram.setVec3("inColor", vec3_get_ptr(triangleColor));

		cube.render();
		shaderProgram.unbind();

		ImGui::PushFont(robotoFont);
		{
			ImGui::Begin("Triangle Info");
			if (ImGui::CollapsingHeader("transform")) {
				if (ImGui::TreeNode("position")) {
					ImGui::SliderFloat("x", &pos.coords.x, -1.0f, 1.0f);
					ImGui::SliderFloat("y", &pos.coords.y, -1.0f, 1.0f);
					ImGui::SliderFloat("z", &pos.coords.z, -1.0f, 1.0f);

					if (ImGui::Button("reset")) {
						pos = vec3();
					}

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("scale")) {
					ImGui::SliderFloat("x", &scale.coords.x, -5.0f, 5.0f);
					ImGui::SliderFloat("y", &scale.coords.y, -5.0f, 5.0f);
					ImGui::SliderFloat("z", &scale.coords.z, -5.0f, 5.0f);

					if (ImGui::Button("reset")) {
						scale = vec3(1.0f, 1.0f, 1.0f);
					}

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("rotation")) {
					ImGui::SliderFloat("x", &rot.coords.x, -180.0f, 180.0f);
					ImGui::SliderFloat("y", &rot.coords.y, -180.0f, 180.0f);
					ImGui::SliderFloat("z", &rot.coords.z, -180.0f, 180.0f);

					if (ImGui::Button("reset")) {
						rot = vec3();
					}

					ImGui::TreePop();
				}
			}
			if (ImGui::CollapsingHeader("color")) {
				ImGui::ColorEdit3("Triangle color", &triangleColor.vals[0]);
			}

			ImGui::End();
		}

		{
			ImGui::Begin("Camera Info");

			if (ImGui::CollapsingHeader("transform")) {
				if (ImGui::TreeNode("position")) {
					ImGui::SliderFloat("x", &cam.pos.coords.x, -10.0f, 10.0f);
					ImGui::SliderFloat("y", &cam.pos.coords.y, -10.0f, 10.0f);
					ImGui::SliderFloat("z", &cam.pos.coords.z, -10.0f, 10.0f);

					cam.target = vec3_add(cam.pos, cam.offset);
					if (ImGui::Button("reset")) {
						cam.pos = vec3(0.0f, 0.0f, 5.0f);
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("rotation")) {
					ImGui::SliderFloat("x", &cam.rot.coords.x, -180.0f, 180.0f);
					ImGui::SliderFloat("y", &cam.rot.coords.y, -180.0f, 180.0f);
					ImGui::SliderFloat("z", &cam.rot.coords.z, -180.0f, 180.0f);
					if (ImGui::Button("reset")) {
						cam.rot = vec3();
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
