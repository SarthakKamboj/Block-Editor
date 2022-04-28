#include "glad/glad.h"
#include "SDL.h"
#include <iostream>
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"

float vertices[] = {
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

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

	int width = 600, height = 400;

	SDL_Window* window = SDL_CreateWindow("window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	bool running = true;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	VAO vao;
	vao.bind();

	EBO ebo;
	ebo.setData(indices, sizeof(indices), GL_STATIC_DRAW);
	ebo.bind();

	VBO vbo;
	vbo.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vbo.unbind();
	vao.unbind();
	ebo.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	ShaderProgram shaderProgram(vertexFilePath, fragmentFilePath);

	uint32_t start = SDL_GetTicks();
	while (running) {

		uint32_t cur = SDL_GetTicks();
		start = cur;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_r) {
					r = (r - 1) * -1;
				}
				else if (event.key.keysym.sym == SDLK_g) {
					g = (g - 1) * -1;
				}
				else if (event.key.keysym.sym == SDLK_b) {
					b = (b - 1) * -1;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}


		glClearColor(r, g, b, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shaderProgram.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		vao.unbind();
		shaderProgram.unbind();

		SDL_GL_SwapWindow(window);

	}

	return 0;
}
