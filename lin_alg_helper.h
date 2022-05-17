#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "ray.h"

glm::mat4 getTranslationMatrix(float x, float y, float z);
glm::mat4 getScaleMatrix(float x, float y, float z);
glm::mat4 getRotMatrix(float x, float y, float z);

const GLfloat* mat4_get_ptr(glm::mat4& mat);

glm::mat4 getProjectionMat(float fov, float near, float far, float aspectRatio);
// ray_t screenToLocalRay(glm::vec2& screenCoords, glm::mat4& proj, glm::mat4& view, glm::mat4& model);
