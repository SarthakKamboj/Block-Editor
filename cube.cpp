#include "cube.h"
#include "input.h"

extern int width, height;
extern mouse_click_state_t mouse_click_state;
extern mouse_state_t mouse_state;

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

Cube::Cube() {
	vbo.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vbo.unbind();

	vao.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();

	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	outlineScale = glm::vec3(1.05f, 1.05f, 1.05f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\vertexShader.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\fragmentShader.frag";
	shaderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	shaderProgram.setFloat("windowHeight", (float)height);

	const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.frag";
	outlineProgram = ShaderProgram(outlineVert, outlineFrag);

	outline = false;
	color = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 dim(1.0f, 1.0f, 1.0f);
	boxCollider = BoxCollider(dim, scale, pos);
}

glm::vec3 screen_to_world(int x, int y) {
	float xNdc = (((float)x) / width * 2.0f) - 1.0f;
	float yNdc = ((-1.0f * (y - height)) / height * 2.0f) - 1.0f;
	float zNdc = 1.0f;
	float wNdc = 1.0f;
	glm::vec4 ndc(xNdc, yNdc, zNdc, wNdc);

	// mat4 projection = getProjectionMat(45.0f, 0.1f, 100.0f, ((float)width) / height);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)width) / height, 0.1f, 100.0f);
	glm::mat4 projInv = glm::inverse(proj);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 viewInv = glm::inverse(view);
	// note that we're translating the scene in the reverse direction of where we want to move

	glm::vec4 worldCoords = viewInv * projInv * ndc;

	glm::vec3 world = glm::vec3(worldCoords.x, worldCoords.y, worldCoords.z);
	// vec3_print(world);

	return world;
}

void Cube::update() {
	boxCollider.transform = pos;

	glm::vec3 point(0.0f, 0.0f, 0.0f);

	if (mouse_click_state.left) {
		glm::vec3 point = screen_to_world(mouse_state.x, mouse_state.y);
		std::cout << mouse_state.x << " " << mouse_state.y << std::endl;
		if (boxCollider.point_collide(point)) {
			outline = !outline;
		}
	}
}

void Cube::render(glm::mat4& projection, glm::mat4& view) {

	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	shaderProgram.bind();

	// glm::mat4 translationMat = getTranslationMatrix(pos.coords.x, pos.coords.y, pos.coords.z);
	glm::mat4 translationMat(1.0f);
	translationMat = glm::translate(translationMat, glm::vec3(pos.x, pos.y, pos.z));
	shaderProgram.setMat4("translate", GL_TRUE, glm::value_ptr(translationMat));
	// shaderProgram.setMat4("translate", GL_TRUE, mat4_get_ptr(translationMat));

	// glm::mat4 rotMat = getRotMatrix(rot.coords.x, rot.coords.y, rot.coords.z);
	glm::mat4 rotMat(1.0f);
	rotMat = glm::rotate(rotMat, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotMat = glm::rotate(rotMat, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotMat = glm::rotate(rotMat, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	shaderProgram.setMat4("rot", GL_TRUE, glm::value_ptr(rotMat));
	// shaderProgram.setMat4("rot", GL_TRUE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat(1.0f);
	// = getScaleMatrix(scale.coords.x, scale.coords.y, scale.coords.z);
	scaleMat = glm::scale(scaleMat, glm::vec3(scale.x, scale.y, scale.z));
	shaderProgram.setMat4("scale", GL_TRUE, glm::value_ptr(scaleMat));
	// shaderProgram.setMat4("scale", GL_TRUE, mat4_get_ptr(scaleMat));

	// shaderProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));
	shaderProgram.setMat4("projection", GL_TRUE, glm::value_ptr(projection));

	// shaderProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));
	shaderProgram.setMat4("view", GL_TRUE, glm::value_ptr(view));
	// shaderProgram.setVec3("inColor", vec3_get_ptr(color));
	shaderProgram.setVec3("inColor", glm::value_ptr(color));

	drawCube();
	shaderProgram.unbind();

	if (outline) {
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		outlineProgram.bind();

		// glm::mat4 translationMat = getTranslationMatrix(pos.coords.x, pos.coords.y, pos.coords.z);
		// outlineProgram.setMat4("translate", GL_TRUE, mat4_get_ptr(translationMat));
		outlineProgram.setMat4("translate", GL_TRUE, glm::value_ptr(translationMat));

		// glm::mat4 rotMat = getRotMatrix(rot.coords.x, rot.coords.y, rot.coords.z);
		// outlineProgram.setMat4("rot", GL_TRUE, mat4_get_ptr(rotMat));
		outlineProgram.setMat4("rot", GL_TRUE, glm::value_ptr(rotMat));

		// glm::mat4 scaleMat = getScaleMatrix(outlineScale.coords.x, outlineScale.coords.y, outlineScale.coords.z);
		glm::mat4 outlineScaleMat(1.0f);
		outlineScaleMat = glm::scale(outlineScaleMat, glm::vec3(outlineScale.x, outlineScale.y, outlineScale.z));
		// outlineProgram.setMat4("scale", GL_TRUE, mat4_get_ptr(scaleMat));
		outlineProgram.setMat4("scale", GL_TRUE, glm::value_ptr(scaleMat));

		// outlineProgram.setMat4("projection", GL_TRUE, mat4_get_ptr(projection));
		outlineProgram.setMat4("projection", GL_TRUE, glm::value_ptr(projection));

		// outlineProgram.setMat4("view", GL_TRUE, mat4_get_ptr(view));
		outlineProgram.setMat4("view", GL_TRUE, glm::value_ptr(view));

		drawCube();
		outlineProgram.unbind();

	}

}

void Cube::drawCube() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(vertices[0])));
	vao.unbind();
}
