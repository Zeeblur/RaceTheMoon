//
// Created by zoe on 10/10/17.
//

#include "input_component.h"
#include "Command.h"
#include "../systems/input_handler.h"
#include <vector>


input_component::input_component(std::shared_ptr<entity> &e) : _parent(e)//, _handler(ih)
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

    //move commands change physics comp.
    // get all commands then execute them.
    std::vector<Command*> commands = input_handler::get()->handle_input();

    for (Command* com : commands)
        com->execute(_parent);

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