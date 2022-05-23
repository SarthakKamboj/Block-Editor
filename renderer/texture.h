#pragma once

#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>

class Texture {
public:
	Texture();
	Texture(const char* filePath, int texUnit);
	void bind();
	void unbind();

	unsigned int texture;
	int texUnit;
};
