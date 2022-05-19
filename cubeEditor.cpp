#include "cubeEditor.h"

CubeEditor::CubeEditor() {
	cube = NULL;

	Arrow xArrow(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -90.0f), Dir::x);
	Arrow yArrow(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), Dir::y);
	Arrow zArrow(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), Dir::z);

	arrows[0] = xArrow;
	arrows[1] = yArrow;
	arrows[2] = zArrow;
}

extern bool editorHover;
void CubeEditor::update() {
	if (cube == NULL) return;

	for (int i = 0; i < sizeof(arrows) / sizeof(arrows[0]); i++) {
		// arrows[i].pos = cube->pos;
		arrows[i].set_position(cube->transform.pos);
		// arrows[i].update();
		// break;
	}

	ImGui::Begin("Triangle Info");

	editorHover |= ImGui::IsWindowHovered() | ImGui::IsAnyItemHovered();

	ImGui::Text(cube->name.c_str());

	if (ImGui::CollapsingHeader("transform")) {
		if (ImGui::TreeNode("position")) {
			ImGui::SliderFloat("x", &cube->transform.pos.x, -3.0f, 3.0f);
			ImGui::SliderFloat("y", &cube->transform.pos.y, -3.0f, 3.0f);
			ImGui::SliderFloat("z", &cube->transform.pos.z, -3.0f, 3.0f);

			if (ImGui::Button("reset")) {
				cube->transform.pos = glm::vec3();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("scale")) {
			ImGui::SliderFloat("x", &cube->transform.scale.x, 0.0f, 5.0f);
			ImGui::SliderFloat("y", &cube->transform.scale.y, 0.0f, 5.0f);
			ImGui::SliderFloat("z", &cube->transform.scale.z, 0.0f, 5.0f);

			if (ImGui::Button("reset")) {
				cube->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("rotation")) {
			ImGui::SliderFloat("x", &cube->transform.rot.x, -180.0f, 180.0f);
			ImGui::SliderFloat("y", &cube->transform.rot.y, -180.0f, 180.0f);
			ImGui::SliderFloat("z", &cube->transform.rot.z, -180.0f, 180.0f);

			if (ImGui::Button("reset")) {
				cube->transform.rot = glm::vec3();
			}

			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("color")) {
		ImGui::ColorEdit3("Triangle color", &cube->color.x);
	}

	ImGui::End();

}

void CubeEditor::render() {
	if (cube == NULL) return;
	for (int i = 0; i < sizeof(arrows) / sizeof(arrows[0]); i++) {
		// arrows[i].render();
		// break;
	}
}
