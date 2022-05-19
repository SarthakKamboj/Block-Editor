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

extern MouseClickState mouse_click_state;
extern MouseState mouse_state;
extern glm::mat4 projection, view;

Arrow::Arrow() {

}

// TODO: make box collider with arrow work 

Arrow::Arrow(glm::vec3 _color, glm::vec3 _rot, Dir dir) {
	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	vao.set_attribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	arrow_shader = ShaderProgram(vertexFilePath, fragmentFilePath);

	collider_dim = glm::vec3(0.4f, 1.0f, 0.1f);
	scale = glm::vec3(0.5f, 0.5f, 0.5f);

	color = _color;
	float highlightAdd = 0.8f;
	highlight_color = glm::vec3(fmin(color.x + highlightAdd, 1.0f), fmin(color.y + highlightAdd, 1.0f), fmin(color.z + highlightAdd, 1.0f));
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
	arrow_shader.set_vec_3("color", glm::value_ptr(color));

	box_collider = BoxCollider(pos, collider_dim * scale, rot);
}

void Arrow::set_position(glm::vec3 _pos) {
	pos = _pos + pos_offset;
}

void Arrow::update() {
	box_collider.transform.pos = pos;
	// boxCollider.rot = rot;
	// boxCollider.scale = scale * colliderDim;

	glm::vec2 screenCoords(mouse_state.x, mouse_state.y);

	Ray ray = box_collider.screen_to_local_ray(screenCoords);

	if (box_collider.ray_collide(ray)) {
		arrow_shader.set_vec_3("color", glm::value_ptr(highlight_color));
	}
	else {
		arrow_shader.set_vec_3("color", glm::value_ptr(color));
	}
}

void Arrow::render() {

	box_collider.render();

	arrow_shader.bind();
	glm::mat4 translationMat = get_translation_matrix(pos.x, pos.y, pos.z);
	arrow_shader.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat = get_rotation_matrix(rot.x, rot.y, rot.z);
	arrow_shader.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = get_scale_matrix(scale.x, scale.y, scale.z);
	arrow_shader.set_mat_4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	arrow_shader.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));

	arrow_shader.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));

	glDisable(GL_DEPTH_TEST);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));
	vao.unbind();

	arrow_shader.unbind();
	glEnable(GL_DEPTH_TEST);
}