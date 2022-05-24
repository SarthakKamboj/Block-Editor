#include "cubeManager.h"

CubeManager::CubeManager() {
	numCubes = 0;
}

void CubeManager::addCube(Transform transform) {
	if (numCubes >= MaxCubes) {
		return;
	}

	for (int i = 0; i < MaxCubes; i++) {
		if (cubes[i] == NULL) {
			Cube* cubeToAdd = new Cube;
			cubeToAdd->transform = transform;
			cubes[i] = cubeToAdd;
			numCubes += 1;
			return;
		}
	}

}

void CubeManager::removeCube(Cube* cubeToRemovePtr) {
	if (cubeToRemovePtr == NULL) return;
	for (int i = 0; i < MaxCubes; i++) {
		if (cubes[i] == cubeToRemovePtr) {
			numCubes -= 1;
			cubes[i] = NULL;
			delete cubeToRemovePtr;
		}
	}
}

void CubeManager::update() {
	for (int i = 0; i < MaxCubes; i++) {
		if (cubes[i] != NULL) {
			cubes[i]->update();
		}
	}

	for (int i = 0; i < MaxCubes; i++) {
		if (cubes[i] != NULL) {
			cubes[i]->lateUpdate();
		}
	}
}

void CubeManager::render() {
	for (int i = 0; i < MaxCubes; i++) {
		if (cubes[i] != NULL) {
			cubes[i]->render();
		}
	}
}
