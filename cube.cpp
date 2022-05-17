#include "cube.h"
#include "input.h"

#include "cube_editor.h"

extern CubeEditor* cubeEditorPtr;

extern int width, height;
extern mouse_click_state_t mouse_click_state;
extern mouse_state_t mouse_state;

int Cube::idx = 0;

extern glm::mat4 projection, view;

static float vertices[] = {
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

	name = "Cube " + std::to_string(Cube::idx);
	Cube::idx += 1;

	// vbo.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	// vbo.unbind();

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

	const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.frag";
	outlineProgram = ShaderProgram(outlineVert, outlineFrag);

	const char* transparentFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\transparent.frag";
	transparentProgram = ShaderProgram(vertexFilePath, transparentFrag);

	outline = false;

	color = glm::vec3(1.0f, 0.0f, 1.0f);

	boxCollider = BoxCollider(pos, scale, rot);
}

void Cube::update(Camera& camera) {
	boxCollider.transform = pos;

	if (mouse_click_state.left) {
		// glm::mat4 proj = getProjectionMat(45.0f, 0.1f, 100.0f, ((float)width) / height);
		// glm::mat4 view = camera.getViewMat();

		/*
		glm::mat4 model(1.0f);
		model = glm::translate(model, pos);
		model = model * getRotMatrix(rot.x, rot.y, rot.z);
		model = glm::scale(model, scale);
		*/

		glm::vec2 screenCoords(mouse_state.x, mouse_state.y);
		ray_t ray = boxCollider.screenToLocalRay(screenCoords);

		if (boxCollider.ray_collide(ray)) {
			cubeEditorPtr->cube = this;
		}
	}
}


void Cube::late_update() {
	outline = (cubeEditorPtr->cube == this);
}

// void Cube::setup_render_outline(glm::mat4& projection, glm::mat4& view) {
void Cube::setup_render_outline() {
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	transparentProgram.bind();

	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	transparentProgram.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat = getRotMatrix(rot.x, rot.y, rot.z);
	transparentProgram.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	transparentProgram.setMat4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	transparentProgram.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

	transparentProgram.setMat4("view", GL_FALSE, mat4_get_ptr(view));
	transparentProgram.setVec3("inColor", glm::value_ptr(color));

	drawCube();
	transparentProgram.unbind();

	glDisable(GL_STENCIL_TEST);


}

//void Cube::render(glm::mat4& projection, glm::mat4& view) {
void Cube::render() {

	shaderProgram.bind();

	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	shaderProgram.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat = getRotMatrix(rot.x, rot.y, rot.z);
	shaderProgram.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	shaderProgram.setMat4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	shaderProgram.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

	shaderProgram.setMat4("view", GL_FALSE, mat4_get_ptr(view));
	shaderProgram.setVec3("inColor", glm::value_ptr(color));

	drawCube();
	shaderProgram.unbind();

	if (outline) {
		outlineProgram.bind();
		outlineProgram.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

		outlineProgram.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

		glm::mat4 outlineScaleMat = getScaleMatrix(outlineScale.x * scale.x, outlineScale.y * scale.y, outlineScale.z * scale.z);
		outlineProgram.setMat4("scale", GL_FALSE, mat4_get_ptr(outlineScaleMat));

		outlineProgram.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

		outlineProgram.setMat4("view", GL_FALSE, mat4_get_ptr(view));
		outlineProgram.unbind();
	}
}


void Cube::render_outline() {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	outlineProgram.bind();
	drawCube();
	outlineProgram.unbind();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
}

void Cube::drawCube() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(vertices[0])));
	vao.unbind();
}
