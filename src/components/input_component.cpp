//
// Created by zoe on 10/10/17.
//

#include "input_component.h"

input_component::input_component(std::shared_ptr<entity> &e) : _parent(e)
{
    _visible = false;
}

bool input_component::initialise()
{
    return true;
}

bool input_component::load_content()
{
    return true;
}

void input_component::update(float delta_time)
{
    // We will just update the entity position.

}

void input_component::render()
{
}

void input_component::unload_content()
{
}

void input_component::shutdown()
{
}