#pragma once

#include "cube.h"
#include "transform.h"

class CubeManager {
public:
	CubeManager();
	void addCube(Transform transform);
	void removeCube(Cube* cube);
	static const int MaxCubes = 200;
	Cube* cubes[MaxCubes] = { 0 };
	int numCubes;

	void update();
	void render();
};
