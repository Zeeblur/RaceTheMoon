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
}

std::shared_ptr<render_component> renderer::build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, effect effType, std::string mesh)
{
    auto _rd = std::make_shared<render_data>();
    _rd->colour = colour;
    _rd->shape = shape;
    _rd->shader = shader;


    // TODO: check if it actually has a model

    if (shape == "rectangle")
        _rd->mesh = gl::generate_rect();
    else if (shape == "plane")
        // This is a pretty hefty way to add objects to the scene, right? - Beej
        _rd->mesh = gl::generate_plane();
    else
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
    //std::cout << "Renderer rendering" << std::endl;
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