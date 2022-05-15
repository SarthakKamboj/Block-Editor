#pragma once

#include "vao.h"
#include "vbo.h"
#include "physics.h"
#include "vec3.h"
#include "mat4.h"
#include "shaderProgram.h"

class Cube {
public:
	Cube();
	void render(mat4& projection, mat4& view);

    vec3 pos;
    vec3 scale;
    vec3 rot;

	vec3 color;
    bool outline;

private:

	VAO vao;
	VBO vbo;
    
	vec3 outlineScale;

    ShaderProgram shaderProgram;
    ShaderProgram outlineProgram;

    void drawCube();
};
