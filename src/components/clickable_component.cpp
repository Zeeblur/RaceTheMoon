#include "clickable_component.h"

clickable_component::clickable_component(std::shared_ptr<entity>&e, clickable_data &data)
    : _parent(e), _data(data)
{
    _visible = false;
    _data.active = true;
}

bool clickable_component::initialise()
{
    return true;
}

bool clickable_component::load_content()
{
    return true;
}

void clickable_component::update(float delta_time)
{
    // Check if mouse is within certain bounds and if it's clicked
    //std::cout << "Checking to see if mouse is within bounds" << std::endl;
}

void clickable_component::render()
{

}

void clickable_component::unload_content()
{
}

void clickable_component::shutdown()
{
}