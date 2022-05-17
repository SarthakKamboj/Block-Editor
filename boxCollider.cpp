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

BoxCollider::BoxCollider() {
	dimensions = glm::vec3(1.0f, 1.0f, 1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform = glm::vec3();

	// const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	colliderProgram.setVec3("color", glm::value_ptr(green));

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
}

BoxCollider::BoxCollider(glm::vec3 _dim, glm::vec3 _scale, glm::vec3 _trans) {
	dimensions = _dim;
	scale = _scale;
	transform = _trans;

	// const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.vert";
	const char* vertexFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\boxCollider.vert";
	const char* fragmentFilePath = "C:\\Sarthak\\voxel_editor\\VoxelEditor\\arrow.frag";
	colliderProgram = ShaderProgram(vertexFilePath, fragmentFilePath);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	colliderProgram.setVec3("color", glm::value_ptr(green));

	vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
	vao.setAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
}

bool BoxCollider::point_collide(glm::vec3& point) {
	return (
		point.x >= (transform.x - (scale.x * dimensions.x / 2.0f)) &&
		point.x <= (transform.x + (scale.x * dimensions.x / 2.0f)) &&
		point.y >= (transform.y - (scale.y * dimensions.y / 2.0f)) &&
		point.y <= (transform.y + (scale.y * dimensions.y / 2.0f)) &&
		point.z >= (transform.z - (scale.y * dimensions.z / 2.0f)) &&
		point.z <= (transform.z + (scale.y * dimensions.z / 2.0f))
		);
}

void BoxCollider::render() {
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);

	colliderProgram.bind();

	// glm::mat4 translationMat = getTranslationMatrix(transform.x, transform.y, transform.z);
	glm::mat4 translationMat(1.0f);
	colliderProgram.setMat4("translate", GL_FALSE, mat4_get_ptr(translationMat));

	glm::mat4 rotMat(1.0f);
	colliderProgram.setMat4("rot", GL_FALSE, mat4_get_ptr(rotMat));

	// glm::mat4 scaleMat = getScaleMatrix(scale.x, scale.y, scale.z);
	glm::mat4 scaleMat(1.0f);
	colliderProgram.setMat4("scale", GL_FALSE, mat4_get_ptr(scaleMat));

	colliderProgram.setMat4("projection", GL_FALSE, mat4_get_ptr(projection));

	colliderProgram.setMat4("view", GL_FALSE, mat4_get_ptr(view));

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (3 * sizeof(vertices[0])));
	vao.unbind();
	colliderProgram.unbind();

	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool BoxCollider::ray_collide(ray_t& ray) {
	glm::vec3 frontCenter(transform.x, transform.y, transform.z + (scale.z * dimensions.z / 2.0f));
	glm::vec3 backCenter(transform.x, transform.y, transform.z - (scale.z * dimensions.z / 2.0f));

	float frontZ = transform.z + (dimensions.z / 2.0f);
	float backZ = transform.z - (dimensions.z / 2.0f);

	float leftX = transform.x + (dimensions.x / 2.0f);
	float rightX = transform.x - (dimensions.x / 2.0f);

	float topY = transform.y + (dimensions.y / 2.0f);
	float bottomY = transform.y - (dimensions.y / 2.0f);

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
