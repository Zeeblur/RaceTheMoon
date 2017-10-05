#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "entity.h"
#include "component.h"
#include "subsystem.h"
#include "glfw.h"

struct render_data
{
    bool visible = false;
    // Let's pretend this is a matrix that was built.
    std::string transform = "(0, 0, 0)";
    std::string colour = "Red";
    std::string shape = "Sphere";
    std::string shader = "Phong";
		// add ref to structs
};
// struct mesh, effect

struct render_component : public component
{
private:
    render_data &_data;

    std::shared_ptr<entity> _parent;
public:
    render_component(std::shared_ptr<entity> e, render_data &data)
        : _parent(e), _data(data)
    {
        _active = false;
        _data.visible = true;
    }

    bool initialise() override final
    {
        return true;
    }

    bool load_content() override final
    {
        return true;
    }

    void update(float delta_time) override final
    {
        // This should never be called.
    }

    void render() override final
    {
        if (_data.visible)
        {
            // "Generate" the transform matrix.
            std::stringstream ss;
            ss << "(" << _parent->get_trans().x << ", " << _parent->get_trans().y << ", " << _parent->get_trans().z << ")" << std::endl;
            _data.transform = ss.str();
        }
    }

    void unload_content() override final
    {

    }

    void shutdown() override final
    {

    }
};

class renderer : public subsystem
{
private:
    std::vector<render_data> _data;

    renderer()
    {
        _active = false;
    }

public:

    inline static std::shared_ptr<renderer> get()
    {
        static std::shared_ptr<renderer> instance(new renderer());
        return instance;
    }

    std::shared_ptr<render_component> build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader)
    {
        _data.push_back(render_data());
        _data.back().colour = colour;
        _data.back().shape = shape;
        _data.back().shader = shader;
        return std::make_shared<render_component>(e, std::ref(_data.back()));
    }

    bool initialise()
    {
        std::cout << "Renderer initialising" << std::endl;
        return true;
    }

    bool load_content()
    {
        std::cout << "Renderer loading content" << std::endl;
        return true;
    }

    void update(float delta_time)
    {
        // Should never be called
        //std::cout << "Renderer updating" << std::endl;

    }

    void render()
    {
        //std::cout << "Renderer rendering" << std::endl;
        // Clear the screen.
        glClear( GL_COLOR_BUFFER_BIT );

        for (auto &d : _data)
        {
            if (d.visible)
            {
                // TODO: open gl calls

                //std::cout << "Rendering " << d.colour << " ";
                //std::cout << d.shape << " using " << d.shader;
                //std::cout << " shading at position " << d.transform << std::endl;
            }
        }

        glfwSwapBuffers(glfw::window);
        glfwPollEvents();
    }

    void unload_content()
    {
        std::cout << "Renderer unloading content" << std::endl;
    }

    void shutdown()
    {
        std::cout << "Renderer shutting down" << std::endl;
    }
};