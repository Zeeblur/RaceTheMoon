#pragma once

#include <iostream>
#include "state_machine.h"

// Engine state 1 will be the menu.
class engine_state_1 : public engine_state
{
public:
    void on_enter()
    {
        // Switch off entities, physics, renderer
        auto m = engine::get()->get_subsystem("entity_manager");
        engine::get()->get_subsystem("entity_manager")->set_active(false);
        engine::get()->get_subsystem("entity_manager")->set_visible(false);
        engine::get()->get_subsystem("physics_system")->set_active(false);
        engine::get()->get_subsystem("renderer")->set_visible(false);
    }

    void on_update(float delta_time)
    {
        std::cout << "********** MENU DISPLAYED ****************" << std::endl;
    }

    void on_exit()
    {

    }
};

// Engine state 2 will be main game
class engine_state_2 : public engine_state
{
public:
    void on_enter()
    {
        // Turn on entities, physics, renderer
        engine::get()->get_subsystem("entity_manager")->set_active(true);
        engine::get()->get_subsystem("entity_manager")->set_visible(true);
        engine::get()->get_subsystem("physics_system")->set_active(true);
        engine::get()->get_subsystem("renderer")->set_visible(true);
    }

    void on_update(float delta_time)
    {
        std::cout << "**************** MAIN GAME RUNNING *****************" << std::endl;
    }

    void on_exit()
    {

    }
};

