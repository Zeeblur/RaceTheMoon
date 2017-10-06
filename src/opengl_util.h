//
// Created by zoe on 06/10/17.
//
#pragma once

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>


namespace gl
{

	void CheckGL();

	void createvao(GLuint &vaoID, GLuint &vertexbuffer, GLuint &programID);

    extern GLuint LoadShaders(char const* vertex_file_path, char const* fragment_file_path);

}
