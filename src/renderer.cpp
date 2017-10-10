#include "renderer.h"
#include <sstream>
#include <fstream>
#include "glfw.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CHECK_GL_ERROR CheckGL(__LINE__, __FILE__)

using namespace glm;

render_component::render_component(std::shared_ptr<entity> e, std::shared_ptr<render_data> data)
	: _parent(e), _data(data)
{
	_active = false;
	_data->visible = true;
}

bool render_component::initialise()
{
	programID = gl::LoadShaders("res/shaders/simple.vert", "res/shaders/simple.frag");
	return true;
}

bool render_component::load_content()
{
	// create vbo
	return true;
}

void render_component::update(float delta_time)
{
	// This should never be called.
}

void render_component::render()
{
	if (_data->visible)
	{
		// "Generate" the transform matrix.
		std::stringstream ss;
		ss << "(" << _parent->get_trans().x << ", " << _parent->get_trans().y << ", " << _parent->get_trans().z << ")" << std::endl;
		_data->transform = ss.str();

		// pass in matrix 

		mat4 projMat_ = glm::perspective(1.0472f, (16.0f / 9.0f), 0.01f, 1000.0f);
		
		mat4 viewMat_ = glm::lookAt(glm::vec3(100.0f), glm::vec3(), glm::vec3(0, 1.0f, 0));

		auto MVP = projMat_ * viewMat_ * mat4(1);
		gl::glData *om = static_cast<gl::glData *>(_data->mesh->GpuData);
		
		glDisable(GL_CULL_FACE);
		//glDisable(GL_DEPTH_TEST);
		

		glUseProgram(programID);
		auto loc = glGetUniformLocation(programID, "MVP");
		glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));

		// Bind the vertex array object for the
		glBindVertexArray(om->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, om->buffers[1]);
		// Check for any OpenGL errors
		if (gl::CHECK_GL_ERROR)
		{
			// Display error
			std::cerr << "ERROR - rendering geometry" << std::endl;
			std::cerr << "Could not bind vertex array object" << std::endl;
			// Throw exception
			throw std::runtime_error("Error rendering geometry");
		}
		// If there is an index buffer then use to render
		if (om->has_indices)
		{
			// Bind index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, om->index_buffer);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not bind index buffer" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}

			// Draw elements
			glDrawElements(om->type, om->indice_count, GL_UNSIGNED_INT, nullptr);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				// Display error
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not draw elements from indices" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}
		}
		else
		{
			// Draw arrays
			glDrawArrays(om->type, 0, om->vertex_count);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not draw arrays" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}
		}
	}
}

void render_component::unload_content()
{

}

void render_component::shutdown()
{

}

renderer::renderer()
{
	_active = false;
}

std::shared_ptr<render_component> renderer::build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, effect effType, std::string mesh)
{
	auto _rd = std::make_shared<render_data>();
	_rd->colour = colour;
	_rd->shape = shape;
	_rd->shader = shader;

	_rd->mesh = gl::loadModel(mesh);

	return std::make_shared<render_component>(e, _rd);
}

bool renderer::initialise()
{
	std::cout << "Renderer initialising" << std::endl;
	return true;
}

bool renderer::load_content()
{
	std::cout << "Renderer loading content" << std::endl;
	return true;
}

void renderer::update(float delta_time)
{
	// Should never be called
	std::cout << "Renderer updating" << std::endl;

}

void renderer::render()
{
	std::cout << "Renderer rendering" << std::endl;
	// Clear the screen.
	//glClearColor(((float)(rand() % 255))/255.0f, 0.2, 0.6, 1.0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);

	for (auto &c : _components)
	{

		if (c->get_visible())
		{
			c->render();
		}
	}

	glfwSwapBuffers(glfw::window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}

void renderer::unload_content()
{
	std::cout << "Renderer unloading content" << std::endl;
}

void renderer::shutdown()
{
	std::cout << "Renderer shutting down" << std::endl;
}