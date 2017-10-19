#include "render_component.h"
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera_component.h"
#include "../systems/camera_system.h"

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

		vec3 transvec = vec3(_parent->get_trans().x, _parent->get_trans().y, _parent->get_trans().z);

		mat4 trans = glm::translate(mat4(1.0f), transvec);

		auto camera = static_cast<camera_component*>(_parent->get_component("camera").get());
		//std::shared_ptr<camera_component> camera = std::static_pointer_cast<camera_component>(_parent->get_component("camera"));
		//auto camera = camera_system::get()->_cameras[0].get();
		mat4 projMat_, viewMat_;
		//projMat_ = camera->get_projection();
		//viewMat_ = camera->get_view();

	/*	if (camera != nullptr)
		{
			projMat_ = camera->get_projection();
			viewMat_ = camera->get_view();
		}
		else*/
		{
			// Perspective projection
			projMat_ = glm::perspective(1.0472f, (16.0f / 9.0f), 0.01f, 1000.0f);
			viewMat_ = glm::lookAt(glm::vec3(100.0f), glm::vec3(), glm::vec3(0, 1.0f, 0));
			// For orthographic projection
			//int width, height;
			//glfwGetWindowSize(glfw::window, &width, &height);
			//projMat_ = glm::ortho(-0.5f * (float)width, 0.5f * (float)width, -0.5f * (float)height, 0.5f * (float)height, -1000.0f, 1000.0f);
		}

		auto MVP = projMat_ * viewMat_ * trans;
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