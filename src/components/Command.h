//
// Created by zoe on 11/10/17.
//

#ifndef RACETHEMOON_COMMAND_H
#define RACETHEMOON_COMMAND_H

#include "glm/glm.hpp"
#include "../entity.h"

using namespace glm;

struct Command
{
    virtual ~Command() {}
    virtual void execute(std::shared_ptr<entity> actor) = 0;
};

struct MoveCommand : public Command
{
    vec3 direction;
    virtual void execute(std::shared_ptr<entity> actor);

    MoveCommand(vec3& dir);
};


#endif //RACETHEMOON_COMMAND_H
