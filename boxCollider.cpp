#include "boxCollider.h"

static float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
};

extern glm::mat4 projection, view;
extern int width, height;

BoxCollider::BoxCollider() {
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 1.0f);
	colliderProgram.setVec3("color", glm::value_ptr(green));

	vao.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
}

BoxCollider::BoxCollider(glm::vec3 _trans, glm::vec3 _scale, glm::vec3 _rot) {
	scale = _scale;
	transform = _trans;
	rot = _rot;

	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	colliderProgram.setVec3("color", glm::value_ptr(color));

	vao.bind();
	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	vao.unbind();
}

void BoxCollider::set_color(glm::vec3 color) {
	colliderProgram.setVec3("color", glm::value_ptr(color));

}

bool BoxCollider::point_collide(glm::vec3& point) {
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
	glDisable(GL_DEPTH_TEST);

	colliderProgram.bind();

	glm::mat4 translationMat = getTranslationMatrix(transform.x, transform.y, transform.z);
	colliderProgram.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat = getRotMatrix(rot.x, rot.y, rot.z);
	colliderProgram.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	colliderProgram.setMat4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	colliderProgram.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

	colliderProgram.setMat4("view", GL_FALSE, mat4_get_ptr(view));

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(vertices[0])));
	vao.unbind();

	colliderProgram.unbind();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool BoxCollider::ray_collide(ray_t& ray) {

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

	glm::vec3 frontColPoint = ray.origin + (ray.dir * unitsToFrontPlane);
	glm::vec3 backColPoint = ray.origin + (ray.dir * unitsToBackPlane);

	glm::vec3 rightColPoint = ray.origin + (ray.dir * unitsToRightPlane);
	glm::vec3 leftColPoint = ray.origin + (ray.dir * unitsToLeftPlane);

	glm::vec3 topColPoint = ray.origin + (ray.dir * unitsToTopPlane);
	glm::vec3 bottomColPoint = ray.origin + (ray.dir * unitsToBottomPlane);

	return point_collide(frontColPoint) || point_collide(backColPoint) ||
		point_collide(rightColPoint) || point_collide(leftColPoint) ||
		point_collide(topColPoint) || point_collide(bottomColPoint);

}

ray_t BoxCollider::screenToLocalRay(glm::vec2& screenCoords) {
	float xNdc = ((float)(screenCoords.x - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenCoords.y - (height / 2.0f))) / (height / 2.0f);
	glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
	glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

	/*
	glm::mat4 translationMat = getTranslationMatrix(transform.x, transform.y, transform.z);
	glm::mat4 rotMat = getRotMatrix(rot.x, rot.y, rot.z);
	// glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	glm::mat4 scaleMat(1.0f);
	glm::mat4 model = translationMat * rotMat * scaleMat;
	*/

	glm::mat4 model(1.0f);
	model = glm::translate(model, transform);
	model = model * getRotMatrix(rot.x, rot.y, rot.z);
	model = glm::scale(model, scale);

	glm::mat4 screenToLocalMat = glm::inverse(projection * view * model);
	glm::vec4 nearCoord = screenToLocalMat * nearNdc;
	glm::vec4 farCoord = screenToLocalMat * farNdc;

	nearCoord /= nearCoord.w;
	farCoord /= farCoord.w;

	glm::vec3 nearVec3(nearCoord.x, nearCoord.y, nearCoord.z);
	glm::vec3 farVec3(farCoord.x, farCoord.y, farCoord.z);
	ray_t ray;
	ray.origin = nearVec3;
	ray.dir = glm::normalize(farVec3 - nearVec3);

	return ray;
}
