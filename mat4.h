#pragma once

#include <cmath>
#include <iostream>
#include <glad/glad.h>
#include "vec4.h"

#define M_PI 3.1415926535897932384626433832795
#define DEG_2_RAD (M_PI / 180.0f)

struct mat4 {
	vec4 rows[4];

	mat4();
	mat4(float identityVal);
};

mat4 getTranslationMatrix(float x, float y, float z);
mat4 getScaleMatrix(float x, float y, float z);
mat4 getRotMatrix(float x, float y, float z);

mat4 mat4_multiply_mat4(mat4 one, mat4 two);
vec4 mat4_multiply_vec4(mat4 one, vec4 two);
void print_mat4(mat4 mat);
const GLfloat* get_ptr(mat4 mat);
