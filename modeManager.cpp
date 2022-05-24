#include "modeManager.h"
#include "cubeEditor.h"
#include "cube.h"
#include "cubeManager.h"
#include <vector>

extern CubeEditor* cubeEditorPtr;
extern CubeManager* cubeManagerPtr;

ModeManager::ModeManager() {
	mode = Mode::SELECT;
	modeString = "select";
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
	if (mode == Mode::SELECT) {
		if (ImGui::Button("delete")) {
			int numCubesSelected = cubeEditorPtr->selectedCubes.size();
			for (int i = 0; i < numCubesSelected; i++) {
				for (int x = 0; x < CubeManager::MaxCubes; x++) {
					if (cubeEditorPtr->selectedCubes[i] == cubeManagerPtr->cubes[x]) {
						cubeManagerPtr->removeCube(cubeManagerPtr->cubes[x]);
					}
				}
			}
			cubeEditorPtr->selectedCubes.clear();
		}
	}
	ImGui::End();
}