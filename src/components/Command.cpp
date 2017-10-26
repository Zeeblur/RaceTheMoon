//
// Created by zoe on 11/10/17.
//

#include "glm/ext.hpp"
#include "Command.h"
#include "physics_component.h"

MoveCommand::MoveCommand(glm::vec3& dir) : direction(dir) {}

void MoveCommand::execute(std::shared_ptr<entity> actor)
{
    // Move command here. to phys
    //std::cout << "Move me " << actor->get_name() << std::endl;

    auto phys = static_cast<physics_component*>(actor->get_component("physics").get());

    if (phys != nullptr)
    {
        phys->add_impulse(direction);
    }

}