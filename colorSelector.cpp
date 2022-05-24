#include "colorSelector.h"
#include "imgui.h"
#include <iostream>
#include "cubeEditor.h"

extern CubeEditor* cubeEditorPtr;

ColorSelector::ColorSelector() {
	for (int i = 0; i < 6; i++) {
		colors[i] = glm::vec3(0.5f, 0.5f, 0.5f);
	}
	customColor = glm::vec3(0.0f, 0.0f, 0.0f);
	replaceIdx = 0;
}

void ColorSelector::update() {
	ImGui::Begin("Color Selector");
	ImGui::Columns(6);
	for (int i = 0; i < 6; i++) {
		glm::vec3& color = colors[i];
		ImVec4 imColor = { color.x, color.y, color.z, 1.0f };

		std::string buttonStr = "Color button " + std::to_string(i);
		if (ImGui::ColorButton(buttonStr.c_str(), imColor)) {
			for (int i = 0; i < cubeEditorPtr->selectedCubes.size(); i++) {
				cubeEditorPtr->selectedCubes[i]->setColor(color);
			}
		}
		ImGui::NextColumn();
	}
	ImGui::Columns(1);
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::ColorEdit3("Triangle color", &customColor.x);
	if (ImGui::Button("add color")) {
		colors[replaceIdx] = customColor;
		replaceIdx += 1;
		if (replaceIdx == colorsSize) {
			replaceIdx = 0;
		}
	}
	ImGui::End();
}