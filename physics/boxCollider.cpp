#include "boxCollider.h"
#include "renderer/renderer.h"
#include "helper/helper.h"

static float vertices[] = {
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
};

static unsigned int indicies[] = {
	0,5,1,0,4,5,
	4,5,6,5,6,7,
	1,0,3,3,2,0,
	7,2,6,7,3,2,
	5,6,7,5,6,1,
	4,3,0,4,3,6
};

extern glm::mat4 projection, view;
extern int width, height;
extern Renderer* rendererPtr;

BoxCollider::BoxCollider() {

	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rot = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	colliderProgram.setVec3("color", glm::value_ptr(color));

	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
	ebo.unbind();
}

BoxCollider::BoxCollider(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) {
	transform.scale = scale;
	transform.pos = pos;
	transform.rot = rot;

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	colliderProgram.setVec3("color", glm::value_ptr(color));

	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
	ebo.unbind();
}

void BoxCollider::setColor(glm::vec3 color) {
	colliderProgram.setVec3("color", glm::value_ptr(color));

}

bool BoxCollider::pointCollide(glm::vec3& point) {
	float extentVal = 0.5f;

	return (
		point.x >= -extentVal &&
		point.x <= extentVal &&
		point.y >= -extentVal &&
		point.y <= extentVal &&
		point.z >= -extentVal &&
		point.z <= extentVal
		);
}

void BoxCollider::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	rendererPtr->submitShader(colliderProgram, transform);

	colliderProgram.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();
	colliderProgram.unbind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

extern bool debugMode;
extern MouseClickState mouseClickState;
bool BoxCollider::rayCollide(Ray& ray) {

	localColPoints.clear();

	glm::vec3& scale = transform.scale;

	float extentVal = 0.5f;
	float frontZ = extentVal, rightX = extentVal, topY = extentVal;
	float backZ = -extentVal, leftX = -extentVal, bottomY = -extentVal;

	float unitsToFrontPlane = (frontZ - ray.origin.z) / ray.dir.z;
	float unitsToBackPlane = (backZ - ray.origin.z) / ray.dir.z;

	float unitsToRightPlane = (rightX - ray.origin.x) / ray.dir.x;
	float unitsToLeftPlane = (leftX - ray.origin.x) / ray.dir.x;

	float unitsToTopPlane = (topY - ray.origin.y) / ray.dir.y;
	float unitsToBottomPlane = (bottomY - ray.origin.y) / ray.dir.y;

	frontColPoint = ray.origin + (ray.dir * unitsToFrontPlane);
	backColPoint = ray.origin + (ray.dir * unitsToBackPlane);

	rightColPoint = ray.origin + (ray.dir * unitsToRightPlane);
	leftColPoint = ray.origin + (ray.dir * unitsToLeftPlane);

	topColPoint = ray.origin + (ray.dir * unitsToTopPlane);
	bottomColPoint = ray.origin + (ray.dir * unitsToBottomPlane);

	bool frontBool = pointCollide(frontColPoint);
	if (frontBool) {
		localColPoints.push_back(frontColPoint);
	}
	bool backBool = pointCollide(backColPoint);
	if (backBool) {
		localColPoints.push_back(backColPoint);
	}
	bool rightBool = pointCollide(rightColPoint);
	if (rightBool) {
		localColPoints.push_back(rightColPoint);
	}
	bool leftBool = pointCollide(leftColPoint);
	if (leftBool) {
		localColPoints.push_back(leftColPoint);
	}
	bool topBool = pointCollide(topColPoint);
	if (topBool) {
		localColPoints.push_back(topColPoint);
	}
	bool bottomBool = pointCollide(bottomColPoint);
	if (bottomBool) {
		localColPoints.push_back(bottomColPoint);
	}

	return frontBool || backBool || rightBool || leftBool || topBool || bottomBool;

}

Ray BoxCollider::screenToLocalRay(glm::vec2& screenCoords) {
	NearFarPointsVec3 points = screenToLocal(screenCoords);

	Ray ray;
	ray.origin = points.nearPoint;
	glm::vec3 diff = points.farPoint - points.nearPoint;
	ray.dir = glm::normalize(diff);

	return ray;
}

NearFarPointsVec3 BoxCollider::screenToLocal(glm::vec2& screenCoords) {
	float xNdc = ((float)(screenCoords.x - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenCoords.y - (height / 2.0f))) / (height / 2.0f);
	glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
	glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

	NearFarPointsVec3 nearFarPoints;
	nearFarPoints.nearPoint = ndcToLocal(nearNdc);
	nearFarPoints.farPoint = ndcToLocal(farNdc);

	return nearFarPoints;
}

glm::vec3 BoxCollider::localToWorld(glm::vec3 localPoint) {
	glm::mat4 translationMat = getTranslationMatrix(transform.pos.x, transform.pos.y, transform.pos.z);
	glm::mat4 rotationMat = getRotationMatrix(transform.rot.x, transform.rot.y, transform.rot.z);
	glm::mat4 scaleMat = getScaleMatrix(transform.scale.x, transform.scale.y, transform.scale.z);
	glm::mat4 model = translationMat * rotationMat * scaleMat;

	glm::vec4 worldPoint = model * glm::vec4(localPoint, 1.0f);

	return glm::vec3(worldPoint.x, worldPoint.y, worldPoint.z);
}

glm::vec3 BoxCollider::ndcToLocal(glm::vec4& ndcCoord) {
	glm::mat4 translationMat = getTranslationMatrix(transform.pos.x, transform.pos.y, transform.pos.z);
	glm::mat4 rotationMat = getRotationMatrix(transform.rot.x, transform.rot.y, transform.rot.z);
	glm::mat4 scaleMat = getScaleMatrix(transform.scale.x, transform.scale.y, transform.scale.z);
	glm::mat4 model = translationMat * rotationMat * scaleMat;

	glm::mat4 ndcToLocalMat = glm::inverse(projection * view * model);

	glm::vec4 localPoint = ndcToLocalMat * ndcCoord;
	localPoint /= localPoint.w;

	return glm::vec3(localPoint.x, localPoint.y, localPoint.z);
}

glm::vec3 BoxCollider::localToLocal(glm::vec3 localPoint) {
	glm::mat4 translationMat = getTranslationMatrix(transform.pos.x, transform.pos.y, transform.pos.z);
	glm::mat4 rotationMat = getRotationMatrix(transform.rot.x, transform.rot.y, transform.rot.z);
	glm::mat4 scaleMat = getScaleMatrix(transform.scale.x, transform.scale.y, transform.scale.z);
	glm::mat4 model = translationMat * rotationMat * scaleMat;

	glm::vec4 newLocal = glm::inverse(projection * view * model) * projection * view * model * glm::vec4(localPoint, 1.0f);
	return glm::vec3(newLocal.x, newLocal.y, newLocal.z);
}

glm::vec4 BoxCollider::localToNDC(glm::vec3 localPoint) {
	glm::mat4 translationMat = getTranslationMatrix(transform.pos.x, transform.pos.y, transform.pos.z);
	glm::mat4 rotationMat = getRotationMatrix(transform.rot.x, transform.rot.y, transform.rot.z);
	glm::mat4 scaleMat = getScaleMatrix(transform.scale.x, transform.scale.y, transform.scale.z);
	glm::mat4 model = translationMat * rotationMat * scaleMat;

	glm::vec4 ndcPoint = projection * view * model * glm::vec4(localPoint, 1.0f);
	ndcPoint /= ndcPoint.w;

	return ndcPoint;
}
