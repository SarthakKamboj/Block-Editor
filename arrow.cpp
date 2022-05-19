#include "arrow.h"

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

extern mouse_click_state_t mouse_click_state;
extern mouse_state_t mouse_state;
extern glm::mat4 projection, view;

Arrow::Arrow() {

}

// TODO: make box collider with arrow work 

Arrow::Arrow(glm::vec3 _color, glm::vec3 _rot, dir_t dir) {
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	vao.setAttribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	arrowShader = ShaderProgram(vertexFilePath, fragmentFilePath);

	colliderDim = glm::vec3(0.4f, 1.0f, 0.1f);
	scale = glm::vec3(0.5f, 0.5f, 0.5f);

	color = _color;
	float highlightAdd = 0.8f;
	highlightColor = glm::vec3(fmin(color.x + highlightAdd, 1.0f), fmin(color.y + highlightAdd, 1.0f), fmin(color.z + highlightAdd, 1.0f));
	rot = _rot;

	if (dir == x) {
		pos_offset = glm::vec3(0.5f, 0.0f, 0.0f);
	}
	else if (dir == y) {
		pos_offset = glm::vec3(0.0f, 0.5f, 0.0f);
	}
	else {
		pos_offset = glm::vec3(0.0f, 0.0f, 0.5f);
	}

	pos_offset *= scale;

	set_position(glm::vec3(0.0f, 0.0f, 0.0f));
	arrowShader.setVec3("color", glm::value_ptr(color));

	boxCollider = BoxCollider(pos, colliderDim * scale, rot);
}

void Arrow::set_position(glm::vec3 _pos) {
	// pos = _pos;
	pos = _pos + pos_offset;
	// boxCollider.transform = pos;
}

void Arrow::update() {
	boxCollider.transform = pos;
	// boxCollider.rot = rot;
	// boxCollider.scale = scale * colliderDim;

	glm::vec2 screenCoords(mouse_state.x, mouse_state.y);

	ray_t ray = boxCollider.screenToLocalRay(screenCoords);

	if (boxCollider.ray_collide(ray)) {
		arrowShader.setVec3("color", glm::value_ptr(highlightColor));
	}
	else {
		arrowShader.setVec3("color", glm::value_ptr(color));
	}
}

void Arrow::render() {

	boxCollider.render();

	arrowShader.bind();
	glm::mat4 translationMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	arrowShader.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat = getRotMatrix(rot.x, rot.y, rot.z);
	arrowShader.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	arrowShader.setMat4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	arrowShader.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

	arrowShader.setMat4("view", GL_FALSE, mat4_get_ptr(view));

	glDisable(GL_DEPTH_TEST);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));
	vao.unbind();

	arrowShader.unbind();
	glEnable(GL_DEPTH_TEST);
}