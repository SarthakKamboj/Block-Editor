#include "arrow.h"
#include "renderer/renderer.h"

static float vertices[] = {
	-0.1f, -0.5f,
	0.1f, -0.5f,
	0.1f, 0.2f,

	-0.1f, 0.2f,
	-0.1f, -0.5f,
	0.1f, 0.2f,

	0.3f, 0.2f,
	0.0f, 0.5f,
	-0.3f, 0.2f
};

extern MouseClickState mouseClickState;
extern MouseState mouseState;
extern Renderer* rendererPtr;
// extern glm::mat4 projection, view;

Arrow::Arrow() {}

// TODO: make box collider with arrow work 

Arrow::Arrow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 _color) {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	vao.setAttribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	arrowShader = ShaderProgram(vertexFilePath, fragmentFilePath);

	colliderDim = glm::vec3(0.4f, 1.0f, 0.1f);
	// colliderDim = glm::vec3(1.0f, 1.0f, 1.0f);

	transform = Transform(pos, rot, scale);

	color = _color;
	float highlightAdd = 0.8f;
	highlightColor = glm::vec3(fmin(color.x + highlightAdd, 1.0f), fmin(color.y + highlightAdd, 1.0f), fmin(color.z + highlightAdd, 1.0f));

	arrowShader.setVec3("color", glm::value_ptr(color));

	boxCollider = BoxCollider(pos, colliderDim * transform.scale, rot);

}

void Arrow::update() {
	boxCollider.transform = transform;
	boxCollider.transform.scale = transform.scale * colliderDim;

	glm::vec2 screenCoords(mouseState.x, mouseState.y);

	Ray ray = boxCollider.screenToLocalRay(screenCoords);

	if (boxCollider.rayCollide(ray)) {
		arrowShader.setVec3("color", glm::value_ptr(highlightColor));
	}
	else {
		arrowShader.setVec3("color", glm::value_ptr(color));
	}
}

void Arrow::render() {

	boxCollider.render();

	rendererPtr->submitShader(arrowShader, transform);

	/*
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	arrowShader.setMat4("translate", GL_FALSE, mat4GetPtr(translationMat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);
	arrowShader.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	arrowShader.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));

	arrowShader.setMat4("projection", GL_FALSE, mat4GetPtr(projection));

	arrowShader.setMat4("view", GL_FALSE, mat4GetPtr(view));
	*/

	glDisable(GL_DEPTH_TEST);

	arrowShader.bind();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));
	vao.unbind();

	arrowShader.unbind();
	glEnable(GL_DEPTH_TEST);
}