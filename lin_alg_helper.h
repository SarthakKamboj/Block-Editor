#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "ray.h"

glm::mat4 get_projection_matrix(float fov, float near, float far, float aspectRatio);
glm::mat4 get_translation_matrix(float x, float y, float z);
glm::mat4 get_scale_matrix(float x, float y, float z);
glm::mat4 get_rotation_matrix(float x, float y, float z);
const GLfloat* mat4_get_ptr(glm::mat4& mat);
