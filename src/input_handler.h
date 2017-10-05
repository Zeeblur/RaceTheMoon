#pragma once

#include <iostream>
#include <memory>
#include "subsystem.h"
#include "state_machine.h"

class input_handler : public subsystem
{
private:
	float _total_time;
    input_handler()
    {
        _visible = false;
		_total_time = 0.f;
    }
public:
    inline static std::shared_ptr<input_handler> get()
    {
        static std::shared_ptr<input_handler> instance(new input_handler());
        return instance;
    }

    bool initialise()
    {
        std::cout << "Input handler initialising" << std::endl;
        return true;
    }

    bool load_content()
    {
        std::cout << "Input handler loading content" << std::endl;
        return true;
    }

    void update(float delta_time)
    {
		_total_time += delta_time;

		// Check every 10 iterations, replace this when an actual clock is added
		if (_total_time >= 20)
		{
			if (glfwGetKey(glfw::window, GLFW_KEY_SPACE))
			{
				std::string state_to_set = "";
				if (engine_state_machine::get()->get_current_state() == "game_state")
				{
					state_to_set = "menu_state"; //engine_state_machine::get()->change_state("menu_state");
				}
				else if (engine_state_machine::get()->get_current_state() == "menu_state")
				{
					state_to_set = "game_state"; //engine_state_machine::get()->change_state("game_state");
				}
					
				// Change state
				std::cout << state_to_set << std::endl;
				engine_state_machine::get()->change_state(state_to_set);
				// Reset timer
				_total_time = 0.f;
			}
			std::cout << engine_state_machine::get()->get_current_state() << (engine_state_machine::get()->get_current_state() == "menu_state") << std::endl;
		}
    }

    void render()
    {
        // This should never be called.
        std::cout << "Input handler rendering" << std::endl;
    }

    void unload_content()
    {
        std::cout << "Input handler unloading content" << std::endl;
    }

    void shutdown()
    {
        std::cout << "Input handler shutting down" << std::endl;
    }
};