#include "cube.h"
#include "input.h"
#include "cubeEditor.h"

extern CubeEditor* cube_editor_ptr;

extern int width, height;
extern MouseClickState mouse_click_state;
extern MouseState mouse_state;

extern bool editor_hover;

int Cube::idx = 0;

extern glm::mat4 projection, view;

static float vertices[] = {
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0
};

static unsigned int indicies[] = {
	0,5,1,0,4,5,
	4,5,6,5,6,7,
	1,0,3,3,2,0,
	7,2,6,7,3,2,
	5,9,8,5,9,1,
	4,11,0,4,11,10
};

Cube::Cube() {

	name = "Cube " + std::to_string(Cube::idx);
	Cube::idx += 1;

	vbo.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);
	ebo.set_data(indicies, sizeof(indicies), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.set_attribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.set_attribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();
	ebo.unbind();

	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	outline_scale = glm::vec3(1.05f, 1.05f, 1.05f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\cube.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\cube.frag";
	shader_program = ShaderProgram(vertexFilePath, fragmentFilePath);

	const char* outlineVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.vert";
	const char* outlineFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\outline.frag";
	outline_program = ShaderProgram(outlineVert, outlineFrag);

	const char* transparentVert = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\transparent.vert";
	const char* transparentFrag = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\transparent.frag";
	transparent_program = ShaderProgram(transparentVert, transparentFrag);

	outline = false;

	color = glm::vec3(0.0f, 0.43f, 1.0f);

	box_collider = BoxCollider(transform.pos, transform.scale, transform.rot);

	const char* texture_file_path = "images\\cube_wall.png";
	texture = Texture(texture_file_path, 0);
}

void Cube::update() {
	box_collider.transform = transform;

	if (mouse_click_state.left && !editor_hover) {
		glm::vec2 screenCoords(mouse_state.x, mouse_state.y);
		Ray ray = box_collider.screen_to_local_ray(screenCoords);

		if (box_collider.ray_collide(ray)) {
			cube_editor_ptr->cube = this;
		}
	}
}


void Cube::late_update() {
	outline = (cube_editor_ptr->cube == this);
}

void Cube::setup_render_outline() {
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	texture.bind();
	shader_program.set_int("texUnit", 0);
	shader_program.bind();

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
	shader_program.set_vec_3("inColor", glm::value_ptr(color));

	drawCube();
	shader_program.unbind();
	texture.unbind();

	glDisable(GL_STENCIL_TEST);

}

void Cube::render() {


	glm::vec3& pos = transform.pos;
	glm::mat4 translationMat = get_translation_matrix(pos.x, pos.y, pos.z);

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = get_rotation_matrix(rot.x, rot.y, rot.z);

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = get_scale_matrix(scale.x, scale.y, scale.z);


	if (!outline) {
		shader_program.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translationMat));
		shader_program.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rotMat));
		shader_program.set_mat_4("scale", GL_FALSE, mat4_get_ptr(scaleMat));
		shader_program.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));
		shader_program.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));
		shader_program.set_vec_3("inColor", glm::value_ptr(color));
		shader_program.set_int("texUnit", 0);

		texture.bind();
		shader_program.bind();
		drawCube();
		shader_program.unbind();
		texture.unbind();
	}
	else {
		outline_program.bind();
		outline_program.set_mat_4("translate", GL_FALSE, mat4_get_ptr(translationMat));
		outline_program.set_mat_4("rot", GL_FALSE, mat4_get_ptr(rotMat));

		glm::mat4 outlineScaleMat = get_scale_matrix(outline_scale.x * scale.x, outline_scale.y * scale.y, outline_scale.z * scale.z);
		outline_program.set_mat_4("scale", GL_FALSE, mat4_get_ptr(outlineScaleMat));

		outline_program.set_mat_4("projection", GL_FALSE, mat4_get_ptr(projection));

		outline_program.set_mat_4("view", GL_FALSE, mat4_get_ptr(view));
		outline_program.unbind();
	}

}


void Cube::render_outline() {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

	outline_program.bind();
	drawCube();
	outline_program.unbind();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

void Cube::drawCube() {
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
}
