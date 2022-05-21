#include "issuesEditor.h"

void printTransformToFile(std::ofstream& file, Transform transform) {
	file << "pos: " << transform.pos.x << ", " << transform.pos.y << ", " << transform.pos.z << "\n";
	file << "scale: " << transform.scale.x << ", " << transform.scale.y << ", " << transform.scale.z << "\n";
	file << "rot: " << transform.rot.x << ", " << transform.rot.y << ", " << transform.rot.z << "\n";
}

void IssuesEditor::Update(std::vector<Cube>& cubes, Camera& cam) {
	ImGui::Begin("issue window");
	if (ImGui::Button("log transforms")) {
		std::ofstream issueFile;
		issueFile.open("issues\\" + std::to_string(rand()) + ".txt");
		issueFile << "camera\n";
		issueFile << "------\n";
		printTransformToFile(issueFile, cam.transform);
		for (int i = 0; i < sizeof(cubes) / sizeof(cubes[0]); i++) {
			issueFile << "\ncube " << i << "\n";
			printTransformToFile(issueFile, cubes[i].transform);
		}
		issueFile.close();

	}
	ImGui::End();
}