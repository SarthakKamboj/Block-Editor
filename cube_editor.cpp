#include "cube_editor.h"

CubeEditor::CubeEditor() {
	cube = NULL;
}

extern bool editorHover;
void CubeEditor::update() {
	if (cube == NULL) return;

	ImGui::Begin("Triangle Info");

	editorHover |= ImGui::IsWindowHovered() | ImGui::IsAnyItemHovered();

	ImGui::Text(cube->name.c_str());

	if (ImGui::CollapsingHeader("transform")) {
		if (ImGui::TreeNode("position")) {
			ImGui::SliderFloat("x", &cube->pos.x, -3.0f, 3.0f);
			ImGui::SliderFloat("y", &cube->pos.y, -3.0f, 3.0f);
			ImGui::SliderFloat("z", &cube->pos.z, -3.0f, 3.0f);

			if (ImGui::Button("reset")) {
				cube->pos = glm::vec3();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("scale")) {
			ImGui::SliderFloat("x", &cube->scale.x, 0.0f, 5.0f);
			ImGui::SliderFloat("y", &cube->scale.y, 0.0f, 5.0f);
			ImGui::SliderFloat("z", &cube->scale.z, 0.0f, 5.0f);

			if (ImGui::Button("reset")) {
				cube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("rotation")) {
			ImGui::SliderFloat("x", &cube->rot.x, -180.0f, 180.0f);
			ImGui::SliderFloat("y", &cube->rot.y, -180.0f, 180.0f);
			ImGui::SliderFloat("z", &cube->rot.z, -180.0f, 180.0f);

			if (ImGui::Button("reset")) {
				cube->rot = glm::vec3();
			}

			ImGui::TreePop();
		}
	}
	if (ImGui::CollapsingHeader("color")) {
		ImGui::ColorEdit3("Triangle color", &cube->color.x);
	}

	ImGui::End();
}
