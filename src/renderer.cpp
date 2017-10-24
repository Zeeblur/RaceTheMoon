#include "renderer.h"
#include <sstream>
#include <fstream>
#include "glfw.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CHECK_GL_ERROR CheckGL(__LINE__, __FILE__)

using namespace glm;

renderer::renderer()
{
    _active = false; 
	programIDs[simple] = std::make_shared<Effect>();
	programIDs[phong] = std::make_shared<Effect>();

	programIDs[simple]->program = gl::LoadShaders("res/shaders/simple.vert", "res/shaders/simple.frag");
	programIDs[phong]->program = gl::LoadShaders("res/shaders/phong.vert", "res/shaders/phong.frag");

}

std::shared_ptr<render_component> renderer::build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, effectType effType)
{
    auto _rd = std::make_shared<render_data>();
    _rd->colour = colour;

    _rd->shader = shader;
    _rd->mesh = gl::load_mesh(shape);
	
	_rd->effect = programIDs[effType];

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

	glfwMakeContextCurrent(glfw::window);
	auto e = glGetError();
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	glViewport(0, 0, x_size, y_size);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	auto err = glGetError();

	glClearColor(0.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);

	// TODO: here can order data by shader then render.
	
	//glUseProgram(programIDs[simple].program);
	auto err2 = glGetError();

	for (auto &r : _dataList)
	{
		auto effect = r->effect->program;
		glUseProgram(effect);

		gl::glData* geom = static_cast<gl::glData *>(r->mesh->GpuData);
		gl::render(geom, effect, r->MVP);
	}

	glfwPollEvents();

    glfwSwapBuffers(glfw::window);
	_dataList.clear();
}

void renderer::unload_content()
{
    std::cout << "Renderer unloading content" << std::endl;
}

void renderer::shutdown()
{
    std::cout << "Renderer shutting down" << std::endl;
}