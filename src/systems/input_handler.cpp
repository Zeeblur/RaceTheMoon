//
// Created by zoe on 10/10/17.
//

#include "input_handler.h"

#include "../entity_manager.h"
#include <fstream>

input_handler::input_handler()
{
    _visible = false;
}

std::shared_ptr<input_component> input_handler::build_component(std::shared_ptr<entity> e)
{
    // create input component and pass in the handler instance
    return std::make_shared<input_component>(e);
}

// Commented out to allow re-adding if ai_system never works
//std::shared_ptr<ai_component> input_handler::build_ai_component(std::shared_ptr<entity> e)
//{
//    // create ai component and pass in handler instance
//    return std::make_shared<ai_component>(e);
//}

bool input_handler::initialise()
{
    std::cout << "Input handler initialising" << std::endl;

    //map buttons

	load_input_settings();

    auto back = glm::vec3(0.0f, 0.0f, 1.0f);
    buttonDown_ = new MoveCommand(back);
    auto left = glm::vec3(-1.0f, 0.0f, 0.0f);
    buttonLeft_ = new MoveCommand(left);
    auto right = glm::vec3(1.0f, 0.0f, 0.0f);
    buttonRight_ = new MoveCommand(right);
    auto forward = glm::vec3(0.0f, 0.0f, -1.0f);
    buttonUp_ = new MoveCommand(forward);

    auto move = glm::vec3(0.0f, 0.0f, -0.2f);
    fakeMove_ = new MoveCommand(move);

    return true;
}

void input_handler::load_input_settings()
{
	std::ifstream user_pref_file;

	user_pref_file.open("res/buttons.txt");
	if (!user_pref_file)
	{
		// Close file, not found
		user_pref_file.close();
		// File not found, create new one with default settings
		std::ofstream user_pref_file_out("res/buttons.txt");
		if (user_pref_file_out.is_open())
		{
			user_pref_file_out << "Left: " << GLFW_KEY_A << "\n";
			user_pref_file_out << "Right: " << GLFW_KEY_D << "\n";
			user_pref_file_out << "Front: " << GLFW_KEY_W << "\n";
			user_pref_file_out << "Back: " << GLFW_KEY_S << "\n";
		}
		// Assign defaults
		glfw_button_left = GLFW_KEY_A;
		glfw_button_right = GLFW_KEY_D;
		glfw_button_up = GLFW_KEY_W;
		glfw_button_down = GLFW_KEY_S;
		// Close file, finished writing
		user_pref_file_out.close();
	}
	std::string input = "";
	// Load in keys from file
	while (user_pref_file >> input)
	{
		if (input._Equal("Left:"))
		{
			user_pref_file >> glfw_button_left;
		}
		else if (input._Equal("Right:"))
		{
			user_pref_file >> glfw_button_right;;
		}
		else if (input._Equal("Front:"))
		{
			user_pref_file >> glfw_button_up;
		}
		else if (input._Equal("Back:"))
		{
			user_pref_file >> glfw_button_down;
		}
	}
	user_pref_file.close();
}

bool input_handler::load_content()
{
    std::cout << "Input handler loading content" << std::endl;
    return true;
}

void input_handler::update(float delta_time)
{
}

void input_handler::render()
{
    // This should never be called.
    std::cout << "Input handler rendering" << std::endl;
}

void input_handler::unload_content()
{
    std::cout << "Input handler unloading content" << std::endl;
}

void input_handler::shutdown()
{
    std::cout << "Input handler shutting down" << std::endl;
}

std::vector<Command*> input_handler::handle_input()
{
    std::vector<Command*> commands;
    if (glfwGetKey(glfw::window, glfw_button_up))
        commands.push_back(buttonUp_);

    if (glfwGetKey(glfw::window, glfw_button_down))
        commands.push_back(buttonDown_);

    if (glfwGetKey(glfw::window, glfw_button_left))
        commands.push_back(buttonLeft_);

    if (glfwGetKey(glfw::window, glfw_button_right))
        commands.push_back(buttonRight_);

    //fake always move forward
    //commands.push_back(fakeMove_);

    return commands;
}
