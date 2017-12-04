//
// Created by beej on 24/11/17.
//

#pragma once
#include <memory>
#include "state_machine.h"
#include <functional>

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

    void static addWaterfallPuzzle(glm::vec3 p);
    void static addCrusher(glm::vec3 p);

    std::map<std::string, std::function<void(glm::vec3 p)>> level_gen_functions;
    
    void addFunc();
};