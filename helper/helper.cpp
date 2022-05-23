#include "helper.h"

void printVec3(glm::vec3& v) {
	std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
}

void printVec4(glm::vec4& v) {
	std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;
}

void printMat4(glm::mat4& v) {
	printVec4(v[0]);
	printVec4(v[1]);
	printVec4(v[2]);
	printVec4(v[3]);
}
