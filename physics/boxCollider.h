#pragma once

#include "math/ray.h"
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "renderer/shaderProgram.h"
#include "renderer/vao.h"
#include "renderer/vbo.h"
#include "renderer/ebo.h"
#include "math/linAlgHelper.h"
#include "transform.h"
#include <vector>
#include "nearFarPoints.h"

class BoxCollider {
public:
	BoxCollider();
	BoxCollider(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

	Transform transform;

	ShaderProgram colliderProgram;

	bool pointCollide(glm::vec3& point);
	bool rayCollide(Ray& point);
	Ray screenToLocalRay(glm::vec2& screenCoords);
	NearFarPointsVec3 screenToLocal(glm::vec2& screenCoords);
	glm::vec3 ndcToLocal(glm::vec4& ndcCoords);
	glm::vec3 localToWorld(glm::vec3 point);
	glm::vec4 localToNDC(glm::vec3 point);
	glm::vec3 localToLocal(glm::vec3 point);

	VAO vao;
	VBO vbo;
	EBO ebo;

	void render();
	void setColor(glm::vec3 color);
	glm::vec3 color;

	glm::vec3 frontColPoint;
	glm::vec3 backColPoint;
	glm::vec3 rightColPoint;
	glm::vec3 leftColPoint;
	glm::vec3 topColPoint;
	glm::vec3 bottomColPoint;

	std::vector<glm::vec3> localColPoints;

};
