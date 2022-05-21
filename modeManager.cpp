#include "modeManager.h"

ModeManager::ModeManager() {
	mode = Mode::ADD;
	modeString = "add";
}

void ModeManager::update() {
	ImGui::Begin("Modes");
	std::string fullModeStr = modeString + " mode";
	ImGui::Text(fullModeStr.c_str());
	if (ImGui::Button("Add")) {
		mode = Mode::ADD;
		modeString = "add";
	}
	if (ImGui::Button("select")) {
		mode = Mode::SELECT;
		modeString = "select";
	}
	ImGui::End();
}