#include "cameraEditor.h"

CameraEditor::CameraEditor(Camera* _camera) {
	cam = _camera;
}

extern bool editor_hover;
void CameraEditor::update() {
	ImGui::Begin("Camera Info");

	if (ImGui::CollapsingHeader("transform")) {
		if (ImGui::TreeNode("position")) {
			ImGui::SliderFloat("x", &cam->transform.pos.x, -10.0f, 10.0f);
			ImGui::SliderFloat("y", &cam->transform.pos.y, -10.0f, 10.0f);
			ImGui::SliderFloat("z", &cam->transform.pos.z, -10.0f, 10.0f);

			if (ImGui::Button("reset")) {
				cam->transform.pos = glm::vec3(0.0f, 0.0f, 5.0f);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("rotation")) {
			ImGui::SliderFloat("x", &cam->transform.rot.x, -180.0f, 180.0f);
			ImGui::SliderFloat("y", &cam->transform.rot.y, -180.0f, 180.0f);
			ImGui::SliderFloat("z", &cam->transform.rot.z, -180.0f, 180.0f);
			if (ImGui::Button("reset")) {
				cam->transform.rot = glm::vec3();
			}
			ImGui::TreePop();
		}
	}

	ImGui::End();


}