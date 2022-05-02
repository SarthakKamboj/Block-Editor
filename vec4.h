#pragma once

#include <iostream>

union vec4 {
	struct {
		float x;
		float y;
		float z;
		float w;
	} coords;

	float vals[4];

public:
	vec4();
	vec4(float x, float y, float z, float w);
};

float dot(vec4 one, vec4 two);
void print_vec4(vec4 vec);