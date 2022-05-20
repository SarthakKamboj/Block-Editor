#include "grid.h"
#include "stb_image.h"
#include "input.h"
#include "cube.h"

static float scale = 20.0f;

extern MouseClickState mouse_click_state;
extern MouseState mouse_state;
extern bool editor_hover;
extern std::vector<Cube> cubes;
extern Camera* cam_ptr;

static float vertices[] = {
	0.5f, 0.5f, scale, scale,
	-0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, scale,
	0.5f, -0.5f, scale, 0.0f
};

static unsigned int indicies[] = {
	0,2,1,3,1,0
};

extern glm::mat4 projection, view;

Grid::Grid() {

	glm::vec3 unit(1.0f, 1.0f, 1.0f);
	transform = Transform(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(90.0f, 0.0f, 0.0f), unit * scale);

	ebo.set_data(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.set_attribute(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	vao.set_attribute(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	vao.unbind();
	ebo.unbind();

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\grid.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\grid.frag";
	shader_program = ShaderProgram(vertexFilePath, fragmentFilePath);

	textureUnit = 0;

	const char* file_path = "images\\grid.png";
	texture = Texture(file_path, textureUnit);

	box_collider = BoxCollider(transform.pos, glm::vec3(scale, scale, 0.1f), transform.rot);
}

void Grid::update() {
	glm::vec2 screenCoords(mouse_state.x, mouse_state.y);
	Ray ray = box_collider.screen_to_local_ray(screenCoords);

	if (!editor_hover && box_collider.ray_collide(ray)) {
		for (int i = 0; i < box_collider.local_col_points.size(); i++) {
			debug_cubes[i].transform.pos = box_collider.local_to_world(box_collider.local_col_points[i]);
		}
		if (mouse_click_state.left) {
			Cube newCube;
			glm::vec3 pos;
			float closestDist = -1;
			for (int i = 0; i < box_collider.local_col_points.size(); i++) {
				glm::vec3 col_world_pos = box_collider.local_to_world(box_collider.local_col_points[0]);
				glm::vec3 camWorldPos = cam_ptr->transform.pos;
				float dist = pow(camWorldPos.x - col_world_pos.x, 2) + pow(camWorldPos.y - col_world_pos.y, 2) + pow(camWorldPos.z - col_world_pos.z, 2);
				if (closestDist == -1) {
					closestDist = dist;
					pos = col_world_pos;
				}
				else if (dist < closestDist) {
					closestDist = dist;
					pos = col_world_pos;
				}
			}
			pos += glm::vec3(0.0f, 0.5f, 0.0f);
			newCube.transform.pos = glm::vec3(round(pos.x), round(pos.y), round(pos.z));
			cubes.push_back(newCube);
		}
	}
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
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	shader_program.unbind();
	texture.unbind();

	box_collider.render();
	for (int i = 0; i < box_collider.local_col_points.size(); i++) {
		debug_cubes[i].render();
	}
}