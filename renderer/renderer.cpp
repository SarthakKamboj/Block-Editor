#include "renderer.h"

Renderer::Renderer() {

}

void Renderer::submitShader(ShaderProgram& shaderProgram, Transform transform) {
	shaderProgram.setMat4("projection", GL_FALSE, glm::value_ptr(projection));
}
