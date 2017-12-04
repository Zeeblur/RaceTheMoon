//
// Created by beej on 24/11/17.
//

#pragma once
#include <memory>
#include "state_machine.h"

class level_gen
{
private:
    level_gen() = default;
public:

    inline static std::shared_ptr<level_gen>& get()
    {
        static std::shared_ptr<level_gen> instance(new level_gen());
        return instance;
    }

    void addWaterfallPuzzle(glm::vec3 p);
};