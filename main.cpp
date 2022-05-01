#include "glad/glad.h"
#include "SDL.h"
#include <iostream>
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shaderProgram.h"
#include "mat.h"

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
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

	int width = 800, height = 800;

	SDL_Window* window = SDL_CreateWindow("window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CCW);

	bool running = true;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	VAO vao;
	vao.bind();

	VBO vbo;
	vbo.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vbo.unbind();

	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vao.unbind();
	// ebo.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	ShaderProgram shaderProgram(vertexFilePath, fragmentFilePath);

	GLfloat pos[3] = { 0.4f, 0.3f, -1.0f };
	GLfloat scale[3] = { 0.75f, 0.5f, 0.8f };
	GLfloat eulerAngles[3] = { 0.0f, 23.4f, 0.0f };

	mat4 translationMat = getTranslationMatrix(pos[0], pos[1], pos[2]);
	mat4 scaleMat = getScaleMatrix(scale[0], scale[1], scale[2]);
	mat4 rotMat = getRotMatrix(eulerAngles[0], eulerAngles[1], eulerAngles[2]);

	vec4 origCoords = vec4(0.5f, 0.25f, 0.2f, 0.5f);
	mat4 mat1 = getTranslationMatrix(10, 15, 20);
	mat4 mat2 = getScaleMatrix(2, 2, 2);
	print_vec4(origCoords);
	std::cout << "\n" << std::endl;
	mat4 combined = mat4_multiply_mat4(mat1, mat2);
	print_mat4(combined);
	std::cout << "\n" << std::endl;
	print_vec4(mat4_multiply_vec4(combined, origCoords));


	// shaderProgram.setVec3("pos", pos);
	// shaderProgram.setVec3("scale", scale);
	// shaderProgram.setVec3("eulerAngles", eulerAngles);

	float yRot = 0.0f;

	uint32_t start = SDL_GetTicks();
	while (running) {

		uint32_t cur = SDL_GetTicks();
		uint32_t diff = cur - start;
		start = cur;

		yRot += (diff / 1000.0f) * 360.0f / 2;

		if (yRot > 360.0f) {
			yRot -= 360.0f;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_r:
					r = (r - 1) * -1;
					break;
				case SDLK_g:
					g = (g - 1) * -1;
					break;
				case SDLK_b:
					b = (b - 1) * -1;
					break;
				case SDLK_ESCAPE:
					running = false;
					break;
				}
			}
		}


		glClearColor(r, g, b, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		shaderProgram.bind();
		vao.bind();

		shaderProgram.setMat4("translate", GL_TRUE, &(translationMat.rows[0].vals[0]));
		shaderProgram.setMat4("scale", GL_TRUE, &(scaleMat.rows[0].vals[0]));
		shaderProgram.setMat4("rot", GL_TRUE, &(rotMat.rows[0].vals[0]));

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(float)));

		mat4 identity(1.0f);

		shaderProgram.setMat4("translate", GL_TRUE, &(identity.rows[0].vals[0]));
		shaderProgram.setMat4("scale", GL_TRUE, &(identity.rows[0].vals[0]));
		shaderProgram.setMat4("rot", GL_TRUE, &(identity.rows[0].vals[0]));

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(float)));

		vao.unbind();
		shaderProgram.unbind();

		SDL_GL_SwapWindow(window);

	}

	return 0;
}
