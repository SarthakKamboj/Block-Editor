#pragma once

#include <iostream>

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
