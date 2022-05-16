#include "boxCollider.h"

BoxCollider::BoxCollider() {
	dimensions = vec3(1.0f, 1.0f, 1.0f);
	scale = vec3(1.0f, 1.0f, 1.0f);
	transform = vec3();
}

BoxCollider::BoxCollider(vec3 _dim, vec3 _scale, vec3 _trans) {
	dimensions = _dim;
	scale = _scale;
	transform = _trans;
}

bool BoxCollider::point_collide(vec3& point) {
	return (
		point.coords.x >= (transform.coords.x - (dimensions.coords.x / 2)) &&
		point.coords.x <= (transform.coords.x + (dimensions.coords.x / 2)) &&
		point.coords.y >= (transform.coords.y - (dimensions.coords.y / 2)) &&
		point.coords.y <= (transform.coords.y + (dimensions.coords.y / 2))
		);
}
