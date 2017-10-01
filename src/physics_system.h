#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "entity.h"
#include "component.h"
#include "subsystem.h"

struct physics_data
{
    bool active = false;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct physics_component : public component
{
private:
    // We'll just keep a reference here.  The physics system
    // will maintain the actual data.
    physics_data &_data;

    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;
public:
    physics_component(std::shared_ptr<entity> &e, physics_data &data)
        : _parent(e), _data(data)
    {
        _visible = false;
        _data.active = true;
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
        // We will just update the entity position.
        _parent->get_trans().x = _data.x;
        _parent->get_trans().y = _data.y;
        _parent->get_trans().z = _data.z;
    }

    void render() override final
    {
    }

    void unload_content() override final
    {
    }

    void shutdown() override final
    {
    }
};

class physics_system : public subsystem
{
private:
    std::vector<physics_data> _data;

    physics_system()
    {
        _visible = false;
    }

public:

    static inline std::shared_ptr<physics_system> get()
    {
        static std::shared_ptr<physics_system> instance = std::shared_ptr<physics_system>(new physics_system());
        return instance;
    }

    std::shared_ptr<physics_component> build_component(std::shared_ptr<entity> e)
    {
        _data.push_back(physics_data());
        return std::make_shared<physics_component>(e, std::ref(_data.back()));
    }

    bool initialise() override final
    {
        std::cout << "Physics system initialising" << std::endl;
        return true;
    }

    bool load_content() override final
    {
        std::cout << "Physics system loading content" << std::endl;
        return true;
    }

    void update(float delta_time) override final
    {
        std::cout << "Physics system updating" << std::endl;
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

    void render() override final
    {
        // This should never be called.
        std::cout << "Physics system rendering" << std::endl;
    }

    void unload_content() override final
    {
        std::cout << "Physics system unloading content" << std::endl;
    }

    void shutdown() override final
    {
        std::cout << "Physics system shutting down" << std::endl;
    }
};