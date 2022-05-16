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

	boxCollider = BoxCollider(glm::vec3(1.0f, 1.0f, 1.0f), scale, pos);
}

void Cube::update(Camera& camera) {
	if (mouse_click_state.left) {

		float xNdc = ((float)(mouse_state.x - (width / 2.0f))) / (width / 2.0f);
		float yNdc = -1.0f * ((float)(mouse_state.y - (height / 2.0f))) / (height / 2.0f);
		glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
		glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

		glm::mat4 proj = _getProjectionMat(45.0f, 0.1f, 100.0f, ((float)width) / height);
		glm::mat4 view = camera.getViewMat();

		glm::mat4 model(1.0f);
		model = glm::translate(model, pos);
		model = model * _getRotMatrix(rot.x, rot.y, rot.z);
		model = glm::scale(model, scale);

		glm::mat4 screenToWorldMat = glm::inverse(proj * view * model);
		glm::vec4 nearCoord = screenToWorldMat * nearNdc;
		glm::vec4 farCoord = screenToWorldMat * farNdc;

		nearCoord /= nearCoord.w;
		farCoord /= farCoord.w;

		glm::vec3 nearVec3(nearCoord.x, nearCoord.y, nearCoord.z);
		ray_t ray;
		ray.origin = nearCoord;
		ray.dir = glm::normalize(farCoord - nearCoord);
		if (boxCollider.ray_collide(ray)) {
			outline = !outline;
		}

	}
}

void Cube::render(glm::mat4& projection, glm::mat4& view) {

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	shaderProgram.bind();

	glm::mat4 translationMat = _getTranslationMatrix(pos.x, pos.y, pos.z);
	shaderProgram.setMat4("translate", GL_FALSE, _mat4_get_ptr(translationMat));

	glm::mat4 rotMat = _getRotMatrix(rot.x, rot.y, rot.z);
	shaderProgram.setMat4("rot", GL_FALSE, _mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = _getScaleMatrix(scale.x, scale.y, scale.z);
	shaderProgram.setMat4("scale", GL_FALSE, _mat4_get_ptr(scaleMat));

	shaderProgram.setMat4("projection", GL_FALSE, _mat4_get_ptr(projection));

	shaderProgram.setMat4("view", GL_FALSE, _mat4_get_ptr(view));
	shaderProgram.setVec3("inColor", glm::value_ptr(color));

	drawCube();
	shaderProgram.unbind();

	if (outline) {
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		outlineProgram.bind();

		outlineProgram.setMat4("translate", GL_FALSE, _mat4_get_ptr(translationMat));

		outlineProgram.setMat4("rot", GL_FALSE, _mat4_get_ptr(rotMat));

		glm::mat4 outlineScaleMat = _getScaleMatrix(outlineScale.x * scale.x, outlineScale.y * scale.y, outlineScale.z * scale.z);
		outlineProgram.setMat4("scale", GL_FALSE, _mat4_get_ptr(outlineScaleMat));

		outlineProgram.setMat4("projection", GL_FALSE, _mat4_get_ptr(projection));

		outlineProgram.setMat4("view", GL_FALSE, _mat4_get_ptr(view));

		drawCube();
		outlineProgram.unbind();

	}

}


void Cube::drawCube() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(vertices[0])));
	vao.unbind();
}
