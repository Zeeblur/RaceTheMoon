#pragma once

#include <iostream>
#include <memory>
#include "subsystem.h"
#include "state_machine.h"

class input_handler : public subsystem
{
private:
    input_handler()
    {
        _visible = false;
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
		
		if (glfwGetKey(glfw::window, GLFW_KEY_SPACE) && engine_state_machine::get()->get_current_state() == "game_state")
		{
			engine_state_machine::get()->change_state("menu_state");
		}

		//if (glfwGetKey(glfw::window, GLFW_KEY_SPACE) && engine_state_machine::get()->get_current_state() == "menu_state")
		//{
		//	engine_state_machine::get()->change_state("game_state");
		//}

        // We are really cheating here.  You should use standard key down
        // checking each frame here.
        //std::cout << "Input handler updating" << std::endl;
        //int choice = 1;
        //std::cout << "Change state to 1 or 2: ";
        //std::cin >> choice;
        //engine_state_machine::get()->change_state(std::to_string(choice));
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