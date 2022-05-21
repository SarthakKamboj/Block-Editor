#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "ray.h"

glm::mat4 getProjectionMatrix(float fov, float near, float far, float aspectRatio);
glm::mat4 getTranslationMatrix(float x, float y, float z);
glm::mat4 getScaleMatrix(float x, float y, float z);
glm::mat4 getRotationMatrix(float x, float y, float z);
const GLfloat* mat4GetPtr(glm::mat4& mat);
