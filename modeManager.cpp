#include "modeManager.h"
#include "cubeEditor.h"
#include "cube.h"
#include <vector>

extern CubeEditor* cubeEditorPtr;

ModeManager::ModeManager() {
	mode = Mode::SELECT;
	modeString = "select";
}

extern std::vector<Cube> cubes;
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
	if (mode == Mode::SELECT) {
		if (ImGui::Button("delete")) {
			int numCubesSelected = cubeEditorPtr->selectedCubes.size();
			// int cubesSize = cubes.size();
			for (int i = 0; i < numCubesSelected; i++) {
				for (int x = 0; x < cubes.size(); x++) {
					if (&cubes[x] == cubeEditorPtr->selectedCubes[i]) {
						cubes.erase(cubes.begin() + x);
						break;
					}
				}
			}
			cubeEditorPtr->selectedCubes.clear();
		}
	}
	ImGui::End();
}