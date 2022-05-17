#include "lin_alg_helper.h"

extern int width, height;

glm::mat4 getTranslationMatrix(float x, float y, float z) {
	glm::mat4 t(1.0f);
	return glm::translate(t, glm::vec3(x, y, z));
}

glm::mat4 getScaleMatrix(float x, float y, float z) {
	glm::mat4 s(1.0f);
	return glm::scale(s, glm::vec3(x, y, z));
}

glm::mat4 getRotMatrix(float x, float y, float z) {
	glm::mat4 r(1.0f);
	r = glm::rotate(r, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	r = glm::rotate(r, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	r = glm::rotate(r, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	return r;
}

const GLfloat* mat4_get_ptr(glm::mat4& mat) {
	return glm::value_ptr(mat);
}

glm::mat4 getProjectionMat(float fov, float near, float far, float aspectRatio) {
	return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

/*
ray_t screenToLocalRay(glm::vec2& screenCoords, glm::mat4& proj, glm::mat4& view, glm::mat4& model) {
	float xNdc = ((float)(screenCoords.x - (width / 2.0f))) / (width / 2.0f);
	float yNdc = -1.0f * ((float)(screenCoords.y - (height / 2.0f))) / (height / 2.0f);
	glm::vec4 nearNdc(xNdc, yNdc, -1.0f, 1.0f);
	glm::vec4 farNdc(xNdc, yNdc, 1.0f, 1.0f);

	glm::mat4 screenToWorldMat = glm::inverse(proj * view * model);
	glm::vec4 nearCoord = screenToWorldMat * nearNdc;
	glm::vec4 farCoord = screenToWorldMat * farNdc;

	nearCoord /= nearCoord.w;
	farCoord /= farCoord.w;

	glm::vec3 nearVec3(nearCoord.x, nearCoord.y, nearCoord.z);
	ray_t ray;
	ray.origin = nearCoord;
	ray.dir = glm::normalize(farCoord - nearCoord);

	return ray;
}
*/
