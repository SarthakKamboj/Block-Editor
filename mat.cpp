#include "mat.h"

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

float dot(vec4 one, vec4 two) {
	vec4 result;
	result.vals[0] = one.vals[0] * two.vals[0];
	result.vals[1] = one.vals[1] * two.vals[1];
	result.vals[2] = one.vals[2] * two.vals[2];
	result.vals[3] = one.vals[3] * two.vals[3];
	return result.vals[0] + result.vals[1] + result.vals[2] + result.vals[3];
}

void print_vec4(vec4 vec) {
	std::cout << vec.vals[0] << " " << vec.vals[1] << " " << vec.vals[2] << " " << vec.vals[3] << std::endl;
}

mat4::mat4() {}

mat4::mat4(float identityVal) {
	rows[0] = vec4(identityVal, 0, 0, 0);
	rows[1] = vec4(0, identityVal, 0, 0);
	rows[2] = vec4(0, 0, identityVal, 0);
	rows[3] = vec4(0, 0, 0, identityVal);
}

mat4 getTranslationMatrix(float x, float y, float z) {
	mat4 mat(1.0f);
	mat.rows[0].vals[3] = x;
	mat.rows[1].vals[3] = y;
	mat.rows[2].vals[3] = z;
	return mat;
}

mat4 getScaleMatrix(float x, float y, float z) {
	mat4 mat(1.0f);
	mat.rows[0].coords.x = x;
	mat.rows[1].coords.y = y;
	mat.rows[2].coords.z = z;
	return mat;
}

mat4 getRotMatrix(float x, float y, float z) {

	float xRot = x * DEG_2_RAD;
	float yRot = y * DEG_2_RAD;
	float zRot = z * DEG_2_RAD;

	mat4 xRotMat = mat4(1.0f);
	xRotMat.rows[1].coords.y = cos(xRot);
	xRotMat.rows[1].coords.z = sin(xRot);
	xRotMat.rows[2].coords.y = -sin(xRot);
	xRotMat.rows[2].coords.z = cos(xRot);

	mat4 yRotMat = mat4(1.0f);
	xRotMat.rows[0].coords.x = cos(yRot);
	xRotMat.rows[0].coords.z = -sin(yRot);
	xRotMat.rows[2].coords.x = sin(yRot);
	xRotMat.rows[2].coords.z = cos(yRot);

	mat4 zRotMat = mat4(1.0f);
	xRotMat.rows[0].coords.x = cos(zRot);
	xRotMat.rows[0].coords.y = sin(zRot);
	xRotMat.rows[1].coords.x = -sin(zRot);
	xRotMat.rows[1].coords.y = cos(zRot);

	return mat4_multiply_mat4(zRotMat, mat4_multiply_mat4(yRotMat, xRotMat));
}

mat4 mat4_multiply_mat4(mat4 one, mat4 two) {
	mat4 result;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			vec4 colVec;
			for (int rr = 0; rr < 4; rr++) {
				colVec.vals[rr] = two.rows[rr].vals[col];
			}
			float val = dot(one.rows[row], colVec);
			result.rows[row].vals[col] = val;
		}
	}
	return result;
}

vec4 mat4_multiply_vec4(mat4 mat, vec4 vec) {
	vec4 result;
	for (int row = 0; row < 4; row++) {
		result.vals[row] = dot(mat.rows[row], vec);
	}
	return result;
}

void print_mat4(mat4 mat) {
	for (int row = 0; row < 4; row++) {
		float* vals = mat.rows[row].vals;
		std::cout << vals[0] << " " << vals[1] << " " << vals[2] << " " << vals[3] << std::endl;
	}
}
