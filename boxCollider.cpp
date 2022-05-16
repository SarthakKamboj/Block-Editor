#include "boxCollider.h"

BoxCollider::BoxCollider() {
	dimensions = glm::vec3(1.0f, 1.0f, 1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform = glm::vec3(0.0f, 0.0f, 0.0f);
}

BoxCollider::BoxCollider(glm::vec3 _dim, glm::vec3 _scale, glm::vec3 _trans) {
	dimensions = _dim;
	scale = _scale;
	transform = _trans;
}

bool BoxCollider::point_collide(glm::vec3& point) {
	return (
		point.x >= (transform.x - (scale.x * dimensions.x / 2)) &&
		point.x <= (transform.x + (scale.x * dimensions.x / 2)) &&
		point.y >= (transform.y - (scale.y * dimensions.y / 2)) &&
		point.y <= (transform.y + (scale.y * dimensions.y / 2))
		// point.coords.z >= (transform.coords.z - (scale.coords.z * dimensions.coords.z / 2)) &&
		// point.coords.z <= (transform.coords.z + (scale.coords.z * dimensions.coords.z / 2))
		);
}
