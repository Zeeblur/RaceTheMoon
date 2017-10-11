//
// Created by zoe on 11/10/17.
//

#include "physics_system.h"

physics_system::physics_system()
{
    _visible = false;
}

std::shared_ptr<physics_component> physics_system::build_component(std::shared_ptr<entity> e)
{
    _data.push_back(physics_data());
    return std::make_shared<physics_component>(e, std::ref(_data.back()));
}

bool physics_system::initialise()
{
    std::cout << "Physics system initialising" << std::endl;
    return true;
}

bool physics_system::load_content()
{
    std::cout << "Physics system loading content" << std::endl;
    return true;
}

void physics_system::update(float delta_time)
{
    //std::cout << "Physics system updating" << std::endl;
    for (auto &d : _data)
    {
        // If active physics object add 1 to each component.
        if (d.active)
        {
            d.x += 1.0f;
            d.y += 1.0f;
            d.z += 1.0f;
        }
    }
}

void physics_system::render()
{
    // This should never be called.
    std::cout << "Physics system rendering" << std::endl;
}

void physics_system::unload_content()
{
    std::cout << "Physics system unloading content" << std::endl;
}

void physics_system::shutdown()
{
    std::cout << "Physics system shutting down" << std::endl;
}
