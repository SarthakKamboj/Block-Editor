#include "vec4.h"

vec4::vec4() {
	coords.x = 0.0f;
	coords.y = 0.0f;
	coords.z = 0.0f;
	coords.w = 0.0f;
}


vec4::vec4(float _x, float _y, float _z, float _w) {
	coords.x = _x;
	coords.y = _y;
	coords.z = _z;
	coords.w = _w;
}

float vec4_dot(vec4 one, vec4 two) {
	vec4 result;
	result.vals[0] = one.vals[0] * two.vals[0];
	result.vals[1] = one.vals[1] * two.vals[1];
	result.vals[2] = one.vals[2] * two.vals[2];
	result.vals[3] = one.vals[3] * two.vals[3];
	return result.vals[0] + result.vals[1] + result.vals[2] + result.vals[3];
}

void vec4_print(vec4 vec) {
	std::cout << vec.vals[0] << " " << vec.vals[1] << " " << vec.vals[2] << " " << vec.vals[3] << std::endl;
}