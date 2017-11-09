//
// Created by zoe on 10/10/17.
//

#include "input_handler.h"

#include "../entity_manager.h"


input_handler::input_handler()
{
    _visible = false;
}

std::shared_ptr<input_component> input_handler::build_component(std::shared_ptr<entity> e)
{
    // create input component and pass in the handler instance
    return std::make_shared<input_component>(e);
}

bool input_handler::initialise()
{
    std::cout << "Input handler initialising" << std::endl;

    //map buttons

    auto back = glm::vec3(0.0f, 0.0f, 1.0f);
    buttonDown_ = new MoveCommand(back);
    auto left = glm::vec3(-1.0f, 0.0f, 0.0f);
    buttonLeft_ = new MoveCommand(left);
    auto right = glm::vec3(1.0f, 0.0f, 0.0f);
    buttonRight_ = new MoveCommand(right);
    auto forward = glm::vec3(0.0f, 0.0f, -1.0f);
    buttonUp_ = new MoveCommand(forward);

    return true;
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

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	const float* axes;
	if (present)
	{
		int count;
		axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		std::cout << "left x: " << axes[0] << std::endl;
		std::cout << "left y: " << axes[1] << std::endl;
		std::cout << "right x: " << axes[2] << std::endl;
		std::cout << "right y: " << axes[3] << std::endl;

		if (axes[1] > 0.2)
			commands.push_back(buttonUp_);

		if (axes[1] < -0.2)
			commands.push_back(buttonDown_);

		if (axes[0] < -0.2)
			commands.push_back(buttonLeft_);

		if (axes[0] > 0.2)
			commands.push_back(buttonRight_);
	}
	else
	{
		if (glfwGetKey(glfw::window, GLFW_KEY_W))
			commands.push_back(buttonUp_);

		if (glfwGetKey(glfw::window, GLFW_KEY_S))
			commands.push_back(buttonDown_);

		if (glfwGetKey(glfw::window, GLFW_KEY_A))
			commands.push_back(buttonLeft_);

		if (glfwGetKey(glfw::window, GLFW_KEY_D))
			commands.push_back(buttonRight_);

	}


    return commands;
}
