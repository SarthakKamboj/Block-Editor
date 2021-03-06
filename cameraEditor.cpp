#include "cameraEditor.h"

CameraEditor::CameraEditor(Camera* _camera) {
	cam = _camera;
}

void CameraEditor::update() {


	ImGui::Begin("Camera Info");

	if (ImGui::CollapsingHeader("transform")) {
		if (ImGui::TreeNode("position")) {
			float max = 40.0f;
			ImGui::SliderFloat("x", &cam->transform.pos.x, -max, max);
			ImGui::SliderFloat("y", &cam->transform.pos.y, -max, max);
			ImGui::SliderFloat("z", &cam->transform.pos.z, -max, max);

			if (ImGui::Button("reset")) {
				cam->transform.pos = glm::vec3(0.0f, 0.0f, 5.0f);
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("rotation")) {
			float max = 180.0f;
			ImGui::SliderFloat("x", &cam->transform.rot.x, -max, max);
			ImGui::SliderFloat("y", &cam->transform.rot.y, -max, max);
			ImGui::SliderFloat("z", &cam->transform.rot.z, -max, max);
			if (ImGui::Button("reset")) {
				cam->transform.rot = glm::vec3();
			}
			ImGui::TreePop();
		}
	}

	ImGui::End();

	cam->update();
}