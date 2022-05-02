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
