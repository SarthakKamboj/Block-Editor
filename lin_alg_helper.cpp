#include "lin_alg_helper.h"

extern int width, height;

glm::mat4 _getTranslationMatrix(float x, float y, float z) {
	glm::mat4 t(1.0f);
	return glm::translate(t, glm::vec3(-x, y, z));
}

glm::mat4 _getScaleMatrix(float x, float y, float z) {
	glm::mat4 s(1.0f);
	return glm::scale(s, glm::vec3(x, y, z));
}

glm::mat4 _getRotMatrix(float x, float y, float z) {
	glm::mat4 r(1.0f);
	r = glm::rotate(r, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	r = glm::rotate(r, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	r = glm::rotate(r, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	return r;
}

const GLfloat* _mat4_get_ptr(glm::mat4& mat) {
	return glm::value_ptr(mat);
}

glm::mat4 _getProjectionMat(float fov, float near, float far, float aspectRatio) {
	return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}
