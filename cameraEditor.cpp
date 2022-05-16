#include "cameraEditor.h"

CameraEditor::CameraEditor(Camera* _camera) {
	cam = _camera;
}

extern bool editorHover;
void CameraEditor::update() {
	ImGui::Begin("Camera Info");

	editorHover |= ImGui::IsWindowHovered();

	if (ImGui::CollapsingHeader("transform")) {
		if (ImGui::TreeNode("position")) {
			ImGui::SliderFloat("x", &cam->pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("y", &cam->pos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("z", &cam->pos.z, -10.0f, 10.0f);

			if (ImGui::Button("reset")) {
				cam->pos = glm::vec3(0.0f, 0.0f, 5.0f);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("rotation")) {
			ImGui::SliderFloat("x", &cam->rot.x, -180.0f, 180.0f);
			ImGui::SliderFloat("y", &cam->rot.y, -180.0f, 180.0f);
			ImGui::SliderFloat("z", &cam->rot.z, -180.0f, 180.0f);
			if (ImGui::Button("reset")) {
				cam->rot = glm::vec3();
			}
			ImGui::TreePop();
		}
	}

	ImGui::End();


}