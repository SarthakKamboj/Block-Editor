/*
#include "vec3.h"

vec3::vec3() {
	vals[0] = 0.0f;
	vals[1] = 0.0f;
	vals[2] = 0.0f;
}

vec3::vec3(float x, float y, float z) {
	vals[0] = x;
	vals[1] = y;
	vals[2] = z;
}

void vec3_print(vec3 vec) {
	std::cout << vec.coords.x << " " << vec.coords.y << " " << vec.coords.z << std::endl;
}

float vec3_mag(vec3 vec) {
	return pow(pow(vec.coords.x, 2) + pow(vec.coords.y, 2) + pow(vec.coords.z, 2), 0.5f);
}

vec3 vec3_normalize(vec3 vec) {
	float m = vec3_mag(vec);
	if (m == 0.0f) {
		std::cout << "normalizing with magnitude 0, making vector 0" << std::endl;
		return vec3(0.0f, 0.0f, 0.0f);
	}
	return vec3(vec.coords.x / m, vec.coords.y / m, vec.coords.z / m);
}

vec3 vec3_sub(vec3 to, vec3 from) {
	return vec3(to.coords.x - from.coords.x, to.coords.y - from.coords.y, to.coords.z - from.coords.z);
}

vec3 vec3_add(vec3 one, vec3 two) {
	return vec3(one.coords.x + two.coords.x, one.coords.y + two.coords.y, one.coords.z + two.coords.z);
}

vec3 vec3_cross(vec3 a, vec3 b) {
	return vec3(a.coords.y * b.coords.z - a.coords.z * b.coords.y, a.coords.z * b.coords.x - a.coords.x * b.coords.z, a.coords.x * b.coords.y - a.coords.y * b.coords.x);
}

vec3 vec3_multiply(vec3 vec, float multiplier) {
	return vec3(vec.coords.x * multiplier, vec.coords.y * multiplier, vec.coords.z * multiplier);
}

float vec3_dot(vec3 one, vec3 two) {
	return (one.coords.x * two.coords.x) + (one.coords.y * two.coords.y) + (one.coords.z * two.coords.z);
}

const GLfloat* vec3_get_ptr(vec3& vec) {
	return &vec.coords.x;
}
*/
