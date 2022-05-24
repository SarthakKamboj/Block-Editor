#pragma once

#include "glm/glm.hpp"

class ColorSelector {
public:
	ColorSelector();
	void update();

private:
	int replaceIdx;
	int colorsSize = 6;
	glm::vec3 colors[6];
	glm::vec3 customColor;
};
