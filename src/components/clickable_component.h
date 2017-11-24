#pragma once
#include "../entity.h"
#include "component.h"
#include <glm/glm.hpp>

struct clickable_data
{
    bool active = false;
    int clicks = 0;
	glm::dvec2 scale;
	glm::dvec2 center;
    std::string parent_name;

};

struct clickable_component : public component
{
private:

    
    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;
public:
	// We'll just keep a reference here.  The clickable system
	// will maintain the actual data.
	clickable_data &_data;

    clickable_component(std::shared_ptr<entity> &e, clickable_data &data);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};