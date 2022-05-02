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

void print_vec3(vec3 vec) {
	std::cout << vec.coords.x << " " << vec.coords.y << " " << vec.coords.z << std::endl;
}

float mag(vec3 vec) {
	return pow(pow(vec.coords.x, 2) + pow(vec.coords.y, 2) + pow(vec.coords.z, 2), 0.5f);
}

vec3 normalize(vec3 vec) {
	float m = mag(vec);
	if (m == 0.0f) {
		std::cout << "normalizing with magnitude 0, making vector 0" << std::endl;
		return vec3(0.0f, 0.0f, 0.0f);
	}
	return vec3(vec.coords.x / m, vec.coords.y / m, vec.coords.z / m);
}

vec3 sub(vec3 from, vec3 to) {
	return vec3(to.coords.x - from.coords.x, to.coords.y - from.coords.y, to.coords.z - from.coords.z);
}

vec3 cross(vec3 a, vec3 b) {
	return vec3(a.coords.y * b.coords.z - a.coords.z * b.coords.y, a.coords.z * b.coords.x - a.coords.x * b.coords.z, a.coords.x * b.coords.y - a.coords.y * b.coords.x);
}
