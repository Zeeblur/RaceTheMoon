#define GLM_ENABLE_EXPERIMENTAL
#include "renderer.h"
#include <sstream>
#include <fstream>
#include "../glfw.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define CHECK_GL_ERROR CheckGL(__LINE__, __FILE__)

using namespace glm;

renderer::renderer()
{
    _active = false; 
	programIDs[simple] = std::make_shared<gl::Effect>();
	programIDs[phong] = std::make_shared<gl::Effect>();
	programIDs[simple_texture] = std::make_shared<gl::Effect>();
	programIDs[text] = std::make_shared<gl::Effect>();
	programIDs[sky] = std::make_shared<gl::Effect>();


	programIDs[simple]->program = gl::LoadShaders("res/shaders/simple.vert", "res/shaders/simple.frag");
	programIDs[phong]->program = gl::LoadShaders("res/shaders/phong.vert", "res/shaders/phong.frag");
	programIDs[simple_texture]->program = gl::LoadShaders("res/shaders/simple_texture.vert", "res/shaders/simple_texture.frag");
	programIDs[text]->program = gl::LoadShaders("res/shaders/text.vert", "res/shaders/text.frag");
	// TODO add lights to effect
	//programIDs[phong]->lights = 
	programIDs[sky]->program = gl::LoadShaders("res/shaders/sky.vert", "res/shaders/sky.frag");
	
}

std::shared_ptr<render_component> renderer::build_component(std::shared_ptr<entity> &e, glm::vec4 colour, std::string texture_path, std::string shape, std::string shader, effectType effType)
{
    auto _rd = std::make_shared<gl::render_data>();
    _rd->matData = gl::material_data();
    _rd->matData._diffuse = colour;
	
	_rd->N = mat3(1.0f);

    _rd->shader = shader;
    _rd->mesh = gl::load_mesh(shape);
	
	_rd->effect = programIDs[effType];
	_rd->effect->name = shader;
	e->get_trans().max = _rd->mesh->max;
	e->get_trans().min = _rd->mesh->min;
	e->get_trans().colType = _rd->mesh->colliderType;

	// add texture stuff
	if (texture_path != "")
		_rd->textureObj = std::make_shared<gl::texture>(gl::texture(texture_path));

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

std::shared_ptr<light_component> renderer::build_light(std::shared_ptr<entity> &e)
{
	auto _ld = std::make_shared<gl::light_data>();

	programIDs[phong]->lights.push_back(_ld);
	//programIDs[sky]->lights.push_back(_ld);

	return std::make_shared<light_component>(e, _ld);
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

	// Enable textures
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glClearColor(0.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);

	// TODO: here can order data by shader then render.
	
	auto err2 = glGetError();

	for (auto &r : _dataList)
	{
		// bind effect
		gl::render(r);
		glBindVertexArray(0);
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