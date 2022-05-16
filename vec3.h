#pragma once

#include <iostream>
#include <cmath>
#include "glad/glad.h"

union vec3 {
	struct {
		float x;
		float y;
		float z;
	} coords;

    struct {
		float r;
		float g;
		float b;
	} colors;

	float vals[3];

public:
	vec3();
	vec3(float x, float y, float z);
};

void vec3_print(vec3 vec);
float vec3_mag(vec3 vec);
vec3 vec3_normalize(vec3 vec);
vec3 vec3_sub(vec3 to, vec3 from);
vec3 vec3_add(vec3 one, vec3 two);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_multiply(vec3 vec, float multiplier);
float vec3_dot(vec3 one, vec3 two);
const GLfloat* vec3_get_ptr(vec3& vec);
