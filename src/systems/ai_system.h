//
// Created by beej on 09/11/17.
//

#pragma once

#include <iostream>
#include <memory>
#include "../subsystem.h"
#include "../state_machine.h"
#include "../components/ai_component.h"
#include "../components/Command.h"

class ai_system : public subsystem
{
private:
    ai_system();

    std::vector<std::shared_ptr<ai_data>> _ai_data;

    //std::vector<input_component> _data;

    // ai movement commands
    Command* aiUp_;

public:

    inline static std::shared_ptr<ai_system> get()
    {
        static std::shared_ptr<ai_system> instance(new ai_system());
        return instance;
    }

    std::shared_ptr<ai_component> build_component(std::shared_ptr<entity> e, unsigned int ai_type, vec3 distance);

    std::vector<Command*> handle_input();
    std::vector<Command*> handle_ai();

    bool initialise();
    bool load_content();
    void update(float delta_time);
    void render();
    void unload_content();
    void shutdown();


};