#include "issuesEditor.h"
#include "cubeManager.h"

void printTransformToFile(std::ofstream& file, Transform transform) {
	file << "pos: " << transform.pos.x << ", " << transform.pos.y << ", " << transform.pos.z << "\n";
	file << "scale: " << transform.scale.x << ", " << transform.scale.y << ", " << transform.scale.z << "\n";
	file << "rot: " << transform.rot.x << ", " << transform.rot.y << ", " << transform.rot.z << "\n";
}

void IssuesEditor::Update(Cube** cubes, Camera& cam) {
	ImGui::Begin("issue window");
	if (ImGui::Button("log transforms")) {
		std::ofstream issueFile;
		issueFile.open("issues\\" + std::to_string(rand()) + ".txt");
		issueFile << "camera\n";
		issueFile << "------\n";
		printTransformToFile(issueFile, cam.transform);
		for (int i = 0; i < CubeManager::MaxCubes; i++) {
			if (cubes[i] == NULL) continue;
			issueFile << "\n" << cubes[i]->name << "\n";
			printTransformToFile(issueFile, cubes[i]->transform);
		}
		issueFile.close();

	}
	ImGui::End();
}