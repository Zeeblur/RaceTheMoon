//
// Created by beej on 08/11/17.
//

#include "ai_component.h"
#include "Command.h"
#include "../systems/input_handler.h"
#include <vector>


ai_component::ai_component(std::shared_ptr<entity> &e) : _parent(e)//, _handler(ih)
{
    _visible = false;
}

bool ai_component::initialise()
{
    return true;
}

bool ai_component::load_content()
{
    return true;
}

void ai_component::update(float delta_time)
{

    // move commands change physics comp.
    // get all commands then execute them.
    std::vector<Command*> commands = input_handler::get()->handle_ai();

    for (Command* com : commands)
        com->execute(_parent);

}

void ai_component::render()
{
}

void ai_component::unload_content()
{
}

void ai_component::shutdown()
{
}