#pragma once

#include <iostream>
#include <cmath>

union vec3 {
	struct {
		float x;
		float y;
		float z;
	} coords;

	float vals[3];

public:
	vec3();
	vec3(float x, float y, float z);
};

void print_vec3(vec3 vec);
float mag(vec3 vec);
vec3 normalize(vec3 vec);
vec3 sub(vec3 one, vec3 two);
vec3 cross(vec3 a, vec3 b);
