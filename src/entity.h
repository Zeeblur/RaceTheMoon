#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "component.h"
#include <iostream>

struct transform
{
    float x = 1.0f;
    float y = 1.0f;
    float z = 1.0f;
};

class entity
{
private:
    // Counter to ID entities
    static size_t counter;

    size_t _id = 0;
    std::string _name = "";
    std::unordered_map<std::string, std::shared_ptr<component>> _components;
    transform _trans;

public:
    inline entity(const std::string& name)
        : _name(name)
    {
        _id = counter++;
    }

    inline transform& get_trans() { return _trans; }

    inline std::string get_name() { return _name; }

    inline bool initialise()
    {
        std::cout << "Entity " << _id << " initialising" << std::endl;
        // Call initialise on all components
        for (auto &c : _components)
            if (!c.second->initialise())
                return false;
        return true;
    }

    inline bool load_content()
    {
        std::cout << "Entity " << _id << " loading content" << std::endl;
        // Call load_content on all components
        for (auto &c : _components)
            if (!c.second->load_content())
                return false;
        return true;
    }

    inline void update(float delta_time)
    {
        //std::cout << "Entity " << _id << " updating" << std::endl;
        //std::cout << _components.size() << std::endl;
        for (auto &c : _components)
            c.second->update(delta_time);
    }

    inline void render()
    {
        //std::cout << "Entity " << _id << " rendering" << std::endl;
        for (auto &c : _components)
            c.second->render();
    }

    inline void unload_content()
    {
        std::cout << "Entity " << _id << " unloading content" << std::endl;
        for (auto &c : _components)
            c.second->unload_content();
    }

    inline void shutdown()
    {
        std::cout << "Entity " << _id << " shutting down" << std::endl;
        for (auto &c : _components)
            c.second->shutdown();
        _components.clear();
    }

    inline bool add_component(const std::string &name, std::shared_ptr<component> comp)
    {
        _components[name] = comp;
        return true;
    }

    inline std::shared_ptr<component> get_component(const std::string &name) const
    {
        auto found = _components.find(name);
        if (found != _components.end())
            return found->second;
        return nullptr;
    }
};