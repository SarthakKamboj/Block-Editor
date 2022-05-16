#include "boxCollider.h"

BoxCollider::BoxCollider() {
	dimensions = glm::vec3(1.0f, 1.0f, 1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform = glm::vec3();
}

BoxCollider::BoxCollider(glm::vec3 _dim, glm::vec3 _scale, glm::vec3 _trans) {
	dimensions = _dim;
	scale = _scale;
	transform = _trans;
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
