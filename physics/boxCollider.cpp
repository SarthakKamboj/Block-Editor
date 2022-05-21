#include "boxCollider.h"

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

BoxCollider::BoxCollider() {

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\shaders\\arrow.frag";
	collider_program = ShaderProgram(vertexFilePath, fragmentFilePath);
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	collider_program.setVec3("color", glm::value_ptr(color));

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
	collider_program = ShaderProgram(vertexFilePath, fragmentFilePath);
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	collider_program.setVec3("color", glm::value_ptr(color));

	ebo.setData(indicies, sizeof(indicies), GL_STATIC_DRAW);
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

	vao.bind();
	ebo.bind();
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
	ebo.unbind();
}

void BoxCollider::set_color(glm::vec3 color) {
	collider_program.setVec3("color", glm::value_ptr(color));

}

bool BoxCollider::pointCollide(glm::vec3& point) {
	glm::vec3& scale = transform.scale;

	return (
		point.x >= (-scale.x / 2.0f) &&
		point.x <= (scale.x / 2.0f) &&
		point.y >= (-scale.y / 2.0f) &&
		point.y <= (scale.y / 2.0f) &&
		point.z >= (-scale.z / 2.0f) &&
		point.z <= (scale.z / 2.0f)
		);
}

void BoxCollider::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glDisable(GL_DEPTH_TEST);

	collider_program.bind();

	glm::vec3& pos = transform.pos;
	glm::mat4 translateMat = getTranslationMatrix(pos.x, pos.y, pos.z);
	collider_program.setMat4("translate", GL_FALSE, mat4GetPtr(translateMat));

	glm::vec3& rot = transform.rot;
	glm::mat4 rotMat = getRotationMatrix(rot.x, rot.y, rot.z);
	collider_program.setMat4("rot", GL_FALSE, mat4GetPtr(rotMat));

	glm::vec3& scale = transform.scale;
	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	collider_program.setMat4("scale", GL_FALSE, mat4GetPtr(scaleMat));

	collider_program.setMat4("projection", GL_FALSE, mat4GetPtr(projection));

	collider_program.setMat4("view", GL_FALSE, mat4GetPtr(view));

	vao.bind();
	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, (void*)0);
	vao.unbind();

	collider_program.unbind();

	// glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool BoxCollider::rayCollide(Ray& ray) {

	localColPoints.clear();

	glm::vec3& scale = transform.scale;

	float frontZ = (scale.z / 2.0f);
	float backZ = -(scale.z / 2.0f);

	float leftX = -(scale.x / 2.0f);
	float rightX = (scale.x / 2.0f);

	float topY = (scale.y / 2.0f);
	float bottomY = -(scale.y / 2.0f);

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

	if (pointCollide(frontColPoint)) {
		localColPoints.push_back(frontColPoint);
	}
	if (pointCollide(backColPoint)) {
		localColPoints.push_back(backColPoint);
	}
	if (pointCollide(rightColPoint)) {
		localColPoints.push_back(rightColPoint);
	}
	if (pointCollide(leftColPoint)) {
		localColPoints.push_back(leftColPoint);
	}
	if (pointCollide(topColPoint)) {
		localColPoints.push_back(topColPoint);
	}
	if (pointCollide(bottomColPoint)) {
		localColPoints.push_back(bottomColPoint);
	}

	return pointCollide(frontColPoint) || pointCollide(backColPoint) ||
		pointCollide(rightColPoint) || pointCollide(leftColPoint) ||
		pointCollide(topColPoint) || pointCollide(bottomColPoint);

}

Ray BoxCollider::screenToLocalRay(glm::vec2& screenCoords) {
	float xNdc = ((float)(screenCoords.x - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenCoords.y - (height / 2.0f))) / (height / 2.0f);
	glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
	glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, transform.pos);
	glm::vec3& rot = transform.rot;
	model = model * getRotationMatrix(rot.x, rot.y, rot.z);
	model = glm::scale(model, transform.scale);

	glm::mat4 screenToLocalMat = glm::inverse(projection * view * model);
	glm::vec4 nearCoord = screenToLocalMat * nearNdc;
	glm::vec4 farCoord = screenToLocalMat * farNdc;

	nearCoord /= nearCoord.w;
	farCoord /= farCoord.w;

	glm::vec3 nearVec3(nearCoord.x, nearCoord.y, nearCoord.z);
	glm::vec3 farVec3(farCoord.x, farCoord.y, farCoord.z);
	Ray ray;
	ray.origin = nearVec3;
	ray.dir = glm::normalize(farVec3 - nearVec3);

	return ray;
}

glm::vec3 BoxCollider::localToWorld(glm::vec3 point) {
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform.pos);
	glm::vec3& rot = transform.rot;
	model = model * getRotationMatrix(rot.x, rot.y, rot.z);
	model = glm::scale(model, transform.scale);

	return model * glm::vec4(point, 1.0f);
}
