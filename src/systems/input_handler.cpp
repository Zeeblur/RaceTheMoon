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
			user_pref_file_out << "NavigationUp: " << GLFW_KEY_UP << "\n";
			user_pref_file_out << "NavigationDown: " << GLFW_KEY_DOWN << "\n";
			user_pref_file_out << "NavigationLeft: " << GLFW_KEY_LEFT << "\n";
			user_pref_file_out << "NavigationRight: " << GLFW_KEY_RIGHT << "\n";
			user_pref_file_out << "JoystickEnter: " << 0 << "\n"; 
			user_pref_file_out << "JoystickUp: " << 10 << "\n";
			user_pref_file_out << "JoystickDown: " << 12 << "\n";
			user_pref_file_out << "JoystickLeft: " << 11 << "\n"; // is this right?
			user_pref_file_out << "JoystickRight: " << 13 << "\n"; // is this right?

		}
		// Assign defaults
		glfw_button_left = GLFW_KEY_A;
		glfw_button_right = GLFW_KEY_D;
		glfw_button_forward = GLFW_KEY_W;
		glfw_button_backward = GLFW_KEY_S;
		glfw_button_navigation_up = GLFW_KEY_UP;
		glfw_button_navigation_down = GLFW_KEY_DOWN;
		glfw_joystick_enter = 0;
		glfw_joystick_up = 10;
		glfw_joystick_left = 11;
		glfw_joystick_down = 12;
		glfw_joystick_right = 13;
		
		// Close file, finished writing
		user_pref_file_out.close();
	}
	std::string input = "";
	// Load in keys from file
	while (user_pref_file >> input)
	{
		if (input == "Left:")
		{
			user_pref_file >> glfw_button_left;
		}
		else if (input == "Right:")
		{
			user_pref_file >> glfw_button_right;;
		}
		else if (input == "Front:")
		{
			user_pref_file >> glfw_button_forward;
		}
		else if (input == "Back:")
		{
			user_pref_file >> glfw_button_backward;
		}
		else if (input == "NavigationUp:")
		{
			user_pref_file >> glfw_button_navigation_up;
		}
		else if (input == "NavigationDown:")
		{
			user_pref_file >> glfw_button_navigation_down;
		}
		else if (input == "NavigationRight:")
		{
			user_pref_file >> glfw_button_navigation_right;
		}
		else if (input == "NavigationLeft:")
		{
			user_pref_file >> glfw_button_navigation_left;
		}
		else if (input == "JoystickEnter:")
		{
			user_pref_file >> glfw_joystick_enter;
		}
		else if (input == "JoystickUp:")
		{
			user_pref_file >> glfw_joystick_up;
		}
		else if (input == "JoystickLeft:")
		{
			user_pref_file >> glfw_joystick_left;
		}
		else if (input == "JoystickDown:")
		{
			user_pref_file >> glfw_joystick_down;
		}
		else if (input == "JoystickRight:")
		{
			user_pref_file >> glfw_joystick_right;
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
    if (glfwGetKey(glfw::window, glfw_button_forward))
        commands.push_back(buttonUp_);

    if (glfwGetKey(glfw::window, glfw_button_backward))
        commands.push_back(buttonDown_);

    if (glfwGetKey(glfw::window, glfw_button_left))
        commands.push_back(buttonLeft_);

    if (glfwGetKey(glfw::window, glfw_button_right))
        commands.push_back(buttonRight_);
	// Check if controller is present
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	int count;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
	// Add hardcoded joystick controls
	if (present && axes[0] < -0.1)
		commands.push_back(buttonLeft_);
	if (present && axes[0] > 0.1)
		commands.push_back(buttonRight_);
	if (present && axes[1] > 0.1)
		commands.push_back(buttonUp_);
	if (present && axes[1] < -0.1)
		commands.push_back(buttonDown_);
    //fake always move forward
    //commands.push_back(fakeMove_);

    return commands;
}
