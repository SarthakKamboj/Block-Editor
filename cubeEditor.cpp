#include "cubeEditor.h"
#include "input/input.h"

extern float deltaTime;
extern MouseClickState mouseClickState;

CubeEditor::CubeEditor() {
	// cube = NULL;

	glm::vec3 pos(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(0.25f, 0.25f, 0.25f);

	transform.pos = pos;
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = scale;

	rightArrow = Arrow(pos + glm::vec3(arrowPosOffset, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -90.0f), scale, glm::vec3(1.0f, 0.0f, 0.0f));
	upArrow = Arrow(pos + glm::vec3(0.0f, arrowPosOffset, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), scale, glm::vec3(0.0f, 1.0f, 0.0f));
	forwardArrow = Arrow(pos + glm::vec3(0.0f, 0.0f, arrowPosOffset), glm::vec3(90.0f, 0.0f, 0.0f), scale, glm::vec3(0.0f, 0.0f, 1.0f));

	leftArrow = Arrow(pos + glm::vec3(-arrowPosOffset, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -90.0f), -scale, glm::vec3(1.0f, 0.0f, 0.0f));
	downArrow = Arrow(pos + glm::vec3(0.0f, -arrowPosOffset, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), -scale, glm::vec3(0.0f, 1.0f, 0.0f));
	backArrow = Arrow(pos + glm::vec3(0.0f, 0.0f, -arrowPosOffset), glm::vec3(90.0f, 0.0f, 0.0f), -scale, glm::vec3(0.0f, 0.0f, 1.0f));

	arrows[0] = &rightArrow;
	arrows[1] = &upArrow;
	arrows[2] = &forwardArrow;
	arrows[3] = &leftArrow;
	arrows[4] = &downArrow;
	arrows[5] = &backArrow;

	// prevFrameCubeSelection = NULL;
	cubeClickedOn = NULL;
	disableSelectionTime = 0.0f;
}

void CubeEditor::addCube(Cube* cubePtr) {
	for (int i = 0; i < selectedCubes.size(); i++) {
		if (selectedCubes[i] == cubePtr) {
			return;
		}
	}
	selectedCubes.push_back(cubePtr);
	disableSelectionTime = 0.25f;
}

void CubeEditor::moveCubes(glm::vec3 offset) {
	for (int i = 0; i < selectedCubes.size(); i++) {
		selectedCubes[i]->transform.pos += offset;
	}
}

extern bool editorHover;
extern std::map<SDL_Keycode, bool> keyDownMap;
void CubeEditor::update() {
	// if (cube == NULL) {

	if (mouseClickState.left) {
		if (cubeClickedOn != NULL) {
			if (keyDownMap[SDLK_LCTRL]) {
				int removeIdx = -1;
				for (int i = 0; i < selectedCubes.size(); i++) {
					if (selectedCubes[i] == cubeClickedOn) {
						removeIdx = i;
						break;
					}
				}
				if (removeIdx != -1) {
					selectedCubes.erase(selectedCubes.begin() + removeIdx);
				}
			}
			else {
				addCube(cubeClickedOn);
			}
		}
		else {
			if (!editorHover) {
				selectedCubes.clear();
			}
		}
	}

	if (selectedCubes.size() == 0) {
		ImGui::Begin("triangle info");
		ImGui::Text("select a cube");
		ImGui::End();
		// prevFrameCubeSelection = NULL;
		return;
	}

	/*
	if (prevFrameCubeSelection != cube) {
		disableSelectionTime = 0.25f;
	}
	*/

	disableSelectionTime = fmax(0.0f, disableSelectionTime - deltaTime);

	// transform.pos = cube->transform.pos;
	transform.pos = selectedCubes[selectedCubes.size() - 1]->transform.pos;
	glm::vec3& pos = transform.pos;

	arrows[0]->transform.pos = pos + glm::vec3(arrowPosOffset, 0.0f, 0.0f);
	arrows[1]->transform.pos = pos + glm::vec3(0.0f, arrowPosOffset, 0.0f);
	arrows[2]->transform.pos = pos + glm::vec3(0.0f, 0.0f, arrowPosOffset);

	arrows[3]->transform.pos = pos + glm::vec3(-arrowPosOffset, 0.0f, 0.0f);
	arrows[4]->transform.pos = pos + glm::vec3(0.0f, -arrowPosOffset, 0.0f);
	arrows[5]->transform.pos = pos + glm::vec3(0.0f, 0.0f, -arrowPosOffset);

	for (int i = 0; i < 6; i++) {
		arrows[i]->update();
	}

	if (disableSelectionTime == 0.0f) {
		if (rightArrow.clickedOn) {
			// cube->transform.pos += glm::vec3(1.0f, 0.0f, 0.0f);
			moveCubes(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (upArrow.clickedOn) {
			// cube->transform.pos += glm::vec3(0.0f, 1.0f, 0.0f);
			moveCubes(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (forwardArrow.clickedOn) {
			// cube->transform.pos += glm::vec3(0.0f, 0.0f, 1.0f);
			moveCubes(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (leftArrow.clickedOn) {
			// cube->transform.pos -= glm::vec3(1.0f, 0.0f, 0.0f);
			moveCubes(glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		if (downArrow.clickedOn) {
			// cube->transform.pos -= glm::vec3(0.0f, 1.0f, 0.0f);
			moveCubes(glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (backArrow.clickedOn) {
			// cube->transform.pos -= glm::vec3(0.0f, 0.0f, 1.0f);
			moveCubes(glm::vec3(0.0f, 0.0f, -1.0f));
		}
	}

	/*
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
	*/

	// prevFrameCubeSelection = cube;

}

void CubeEditor::render() {
	// if (cube == NULL) return;
	if (selectedCubes.size() == 0) return;

	// cube->renderOutline();
	for (int i = 0; i < selectedCubes.size(); i++) {
		selectedCubes[i]->renderOutline();
	}

	for (int i = 0; i < 6; i++) {
		arrows[i]->render();
	}
}

void CubeEditor::setupOutline() {
	// if (cube == NULL) return;
	if (selectedCubes.size() == 0) return;
	// cube->setupRenderOutline();
	for (int i = 0; i < selectedCubes.size(); i++) {
		selectedCubes[i]->setupRenderOutline();
	}
}
