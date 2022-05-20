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

Arrow::Arrow() {}

// TODO: make box collider with arrow work 

Arrow::Arrow(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec3 _color) {
	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	vao.set_attribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	vao.unbind();

	const char* vertex_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* fragment_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	arrow_shader = ShaderProgram(vertex_file_path, fragment_file_path);

	collider_dim = glm::vec3(0.4f, 1.0f, 0.1f);
	// collider_dim = glm::vec3(1.0f, 1.0f, 1.0f);

	transform = Transform(pos, rot, scale);

	color = _color;
	float highlight_add = 0.8f;
	highlight_color = glm::vec3(fmin(color.x + highlight_add, 1.0f), fmin(color.y + highlight_add, 1.0f), fmin(color.z + highlight_add, 1.0f));

	arrow_shader.set_vec_3("color", glm::value_ptr(color));

	box_collider = BoxCollider(pos, collider_dim * transform.scale, rot);

}

void Arrow::update() {
	box_collider.transform = transform;
	box_collider.transform.scale = transform.scale * collider_dim;

	glm::vec2 screen_coords(mouse_state.x, mouse_state.y);

	Ray ray = box_collider.screen_to_local_ray(screen_coords);

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
	glm::vec3& pos = transform.pos;
	glm::mat4 translation_mat = get_translation_matrix(pos.x, pos.y, pos.z);
	arrow_shader.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translation_mat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rot_mat = get_rotation_matrix(rot.x, rot.y, rot.z);
	arrow_shader.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rot_mat));

	glm::vec3& scale = transform.scale;
	glm::mat4 scale_mat = get_scale_matrix(scale.x, scale.y, scale.z);
	arrow_shader.set_mat_4("scale", GL_FALSE, mat4_get_ptr(scale_mat));

	arrow_shader.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));

	arrow_shader.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));

	glDisable(GL_DEPTH_TEST);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));
	vao.unbind();

	arrow_shader.unbind();
	glEnable(GL_DEPTH_TEST);
}