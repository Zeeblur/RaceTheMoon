#pragma once

#include <iostream>
#include <memory>
#include "../subsystem.h"
#include "../state_machine.h"
#include "../components/input_component.h"
#include "../components/Command.h"

class input_handler : public subsystem
{
private:
    input_handler();

    //std::vector<input_component> _data;

    // button references
    Command* buttonUp_;
    Command* buttonDown_;
    Command* buttonLeft_;
    Command* buttonRight_;

public:

    inline static std::shared_ptr<input_handler> get()
    {
        static std::shared_ptr<input_handler> instance(new input_handler());
        return instance;
    }

    std::shared_ptr<input_component> build_component(std::shared_ptr<entity> e);

    std::vector<Command*> handle_input();

    bool initialise();
    bool load_content();
    void update(float delta_time);
    void render();
    void unload_content();
    void shutdown();


};