#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

glm::mat4 _getTranslationMatrix(float x, float y, float z);
glm::mat4 _getScaleMatrix(float x, float y, float z);
glm::mat4 _getRotMatrix(float x, float y, float z);

const GLfloat* _mat4_get_ptr(glm::mat4& mat);

glm::mat4 _getProjectionMat(float fov, float near, float far, float aspectRatio);
