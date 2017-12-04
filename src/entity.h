#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <string>
#include <unordered_map>
#include <memory>
#include "components/component.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct transform_data
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

	glm::quat rotation = glm::quat();
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 max = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 min = glm::vec3(0.0f, 0.0f, 0.0f);

    int colType = 0;
};

class entity
{
private:
    // Counter to ID entities
    static size_t counter;

    size_t _id = 0;
    std::string _name = "";
    std::unordered_map<std::string, std::shared_ptr<component>> _components;
	transform_data _trans;

public:
	// Used to keep track of which state this entity belongs to
	int state;
	inline entity(const std::string& name, transform_data trans)
		: _name(name), _trans(trans)
	{
		_id = counter++;
	}

    inline transform_data& get_trans() { return _trans; }

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