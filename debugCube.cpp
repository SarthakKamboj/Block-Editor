#include "debugCube.h"

extern glm::mat4 projection, view;

static float vertices[] = {
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
};

static unsigned int indicies[] = {
	0,5,1,0,4,5,
	4,5,6,5,6,7,
	1,0,3,3,2,0,
	7,2,6,7,3,2,
	5,6,7,5,6,1,
	4,3,0,4,3,6
};

DebugCube::DebugCube() {

	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.set_data(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.set_attribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
	ebo.unbind();

	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	const char* vertex_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\boxCollider.vert";
	const char* fragment_file_path = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	shader_program = ShaderProgram(vertex_file_path, fragment_file_path);

	shader_program.set_vec_3("color", glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
}

void DebugCube::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = get_translation_matrix(pos.x, pos.y, pos.z);

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = get_rotation_matrix(rot.x, rot.y, rot.z);

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = get_scale_matrix(scale.x, scale.y, scale.z);

	shader_program.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translationMat));
	shader_program.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rotMat));
	shader_program.set_mat_4("scale", GL_FALSE, mat4_get_ptr(scaleMat));
	shader_program.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));
	shader_program.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));

	shader_program.bind();
	drawCube();
	shader_program.unbind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void DebugCube::drawCube() {
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
}