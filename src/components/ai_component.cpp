//
// Created by beej on 08/11/17.
//

#include "ai_component.h"
#include "Command.h"
#include "../systems/input_handler.h"
#include <vector>


ai_component::ai_component(std::shared_ptr<entity> &e, std::shared_ptr<ai_data> &ai_data) : _parent(e), _ai_data(ai_data)
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

    _ai_data->cur_pos = glm::vec3(_parent->get_trans().x, _parent->get_trans().y, _parent->get_trans().z);
    // move commands change physics comp.
    // get all commands then execute them.
   // std::vector<Command*> commands = input_handler::get()->handle_ai();

    std::vector<Command*> commands = ai_system::get()->handle_ai(_ai_data);

    //std::cout << "parent name: " << _parent->get_name() << "command vector size: " << commands.size() << std::endl;
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