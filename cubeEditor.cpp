#include "cubeEditor.h"

CubeEditor::CubeEditor() {
	cube = NULL;

	glm::vec3 pos(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(0.5f, 0.5f, 0.5f);

	transform.pos = pos;
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = scale;

	xArrow = Arrow(pos + (glm::vec3(0.5f, 0.0f, 0.0f) * scale), glm::vec3(0.0f, 0.0f, -90.0f), scale, glm::vec3(1.0f, 0.0f, 0.0f));
	yArrow = Arrow(pos + (glm::vec3(0.0f, 0.5f, 0.0f) * scale), glm::vec3(0.0f, 0.0f, 0.0f), scale, glm::vec3(0.0f, 1.0f, 0.0f));
	zArrow = Arrow(pos + (glm::vec3(0.0f, 0.0f, 0.5f) * scale), glm::vec3(90.0f, 0.0f, 0.0f), scale, glm::vec3(0.0f, 0.0f, 1.0f));

	arrows[0] = xArrow;
	arrows[1] = yArrow;
	arrows[2] = zArrow;
}

extern bool editorHover;
void CubeEditor::update() {
	if (cube == NULL) {
		ImGui::Begin("triangle info");
		ImGui::Text("select a cube");
		ImGui::End();
		return;
	}

	glm::vec3& pos = cube->transform.pos;
	glm::vec3& scale = transform.scale;

	xArrow.transform.pos = pos + (glm::vec3(0.5f, 0.0f, 0.0f) * scale);
	yArrow.transform.pos = pos + (glm::vec3(0.0f, 0.5f, 0.0f) * scale);
	zArrow.transform.pos = pos + (glm::vec3(0.0f, 0.0f, 0.5f) * scale);

	xArrow.update();
	yArrow.update();
	zArrow.update();

	ImGui::Begin("triangle info");

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

	cube->renderOutline();
	xArrow.render();
	yArrow.render();
	zArrow.render();
}

void CubeEditor::setupOutline() {
	if (cube == NULL) return;
	cube->setupRenderOutline();
}
