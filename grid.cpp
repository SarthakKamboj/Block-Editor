#include "grid.h"
#include "stb_image.h"

static float scale = 20.0f;

static float vertices[] = {
	0.5f, 0.5f, scale, scale,
	-0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, scale,

	0.5f, 0.5f, scale, scale,
	-0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, scale, 0.0f
};

extern glm::mat4 projection, view;

Grid::Grid() {

	glm::vec3 unit(1.0f, 1.0f, 1.0f);
	transform = Transform(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(90.0f, 0.0f, 0.0f), unit * scale);

	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.bind();
	vao.set_attribute(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.set_attribute(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	vao.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\grid.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\grid.frag";
	shader_program = ShaderProgram(vertexFilePath, fragmentFilePath);

	textureUnit = 0;

	const char* file_path = "images\\grid.png";
	texture = Texture(file_path, textureUnit);
}

void Grid::render() {
	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = get_translation_matrix(pos.x, pos.y, pos.z);
	shader_program.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = get_rotation_matrix(rot.x, rot.y, rot.z);
	shader_program.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = get_scale_matrix(scale.x, scale.y, scale.z);
	shader_program.set_mat_4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	shader_program.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));
	shader_program.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));

	shader_program.set_int("texUnit", textureUnit);
	shader_program.bind();

	texture.bind();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (4 * sizeof(vertices[0])));
	vao.unbind();
	shader_program.unbind();
	texture.unbind();
}