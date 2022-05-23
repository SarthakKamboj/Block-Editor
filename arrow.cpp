#include "arrow.h"
#include "renderer/renderer.h"

/*
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
*/

/*
static float vertices[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, 0.25f, 0.5f,
	0.5f, 0.25f, 0.5f,
	0.0f, 0.25f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.0f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f
};

static unsigned int indicies[] = {
	0,1,2,
	0,1,3,
	0,2,3,
	1,2,4,
	2,4,6,
	1,3,5,
	1,5,4,
	2,3,5,
	2,5,6,
	4,5,6
};
*/

/*
static float vertices[] = {
	0.0f, 0.5f, 0.0f, 0.5f, 0.75f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.5f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.5f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.5f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f
};
*/

static float vertices[] = {
	0.0f, 0.5f, 0.0f, 0.5f, 0.75f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.5f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.5f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.5f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f
};

static unsigned int indicies[] = {
	0,1,2,
	0,2,3,
	0,3,4,
	0,1,4,

	5,6,7,
	5,7,8
};

extern MouseClickState mouseClickState;
extern MouseState mouseState;
extern Renderer* rendererPtr;

Arrow::Arrow() {}

Arrow::Arrow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 _color) {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.setAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	arrowShader = ShaderProgram(vertexFilePath, fragmentFilePath);

	transform = Transform(pos, rot, scale);

	color = _color;
	float highlightAdd = 0.8f;
	highlightColor = glm::vec3(fmin(color.x + highlightAdd, 1.0f), fmin(color.y + highlightAdd, 1.0f), fmin(color.z + highlightAdd, 1.0f));

	boxCollider = BoxCollider(pos, transform.scale, rot);
}

void Arrow::update() {
	clickedOn = false;
	boxCollider.transform = transform;

	glm::vec2 screenCoords(mouseState.x, mouseState.y);

	Ray ray = boxCollider.screenToLocalRay(screenCoords);

	if (boxCollider.rayCollide(ray)) {
		arrowShader.setVec3("color", glm::value_ptr(highlightColor));
		clickedOn = mouseClickState.left;
	}
	else {
		arrowShader.setVec3("color", glm::value_ptr(color));
	}
}

void Arrow::render() {
	glDisable(GL_DEPTH_TEST);

	rendererPtr->submitShader(arrowShader, transform);
	arrowShader.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	arrowShader.unbind();

	glEnable(GL_DEPTH_TEST);
}