#include "pause_state.h"
#include "entity_manager.h"
#include "systems/clickable_system.h"
#include <iostream>
#include "engine_state_machine.h"
void pause_state::initialise()
{
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	// Pause text transform
	transform_data paused_transform;
	paused_transform.x = x_size / 2 - 100;
	paused_transform.y = y_size - 50;
	// Pause
	auto paused_text = entity_manager::get()->create_entity("pause", state_type::PAUSE, paused_transform);
	paused_text->add_component("render", renderer::get()->build_component(paused_text, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	paused_text->add_component("text", text_system::get()->build_component(paused_text, "PAUSED"));

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size * 0.5, y_size * 0.5, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::PAUSE, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));



	int x_button_size = 100;
	int y_button_size = 50;

	// button trans
	transform_data continue_button_transform;
	continue_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	continue_button_transform.y = 0.0f;
	transform_data menu_button_transform;
	menu_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	menu_button_transform.y = -125.0f;

	// Y offset between buttons
	int button_offset = 125;

	// Continue button
	auto button_continue = entity_manager::get()->create_entity("continue_button", state_type::PAUSE, continue_button_transform);

	button_continue->add_component("render", renderer::get()->build_component(button_continue, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/continue_button_selected.png", "rectangle", "Gouraud", simple_texture));
	button_continue->add_component("clickable", clickable_system::get()->build_component(button_continue, glm::dvec2(0, 0), glm::dvec2(x_button_size, y_button_size)));
	button_continue->add_component("camera", camera_system::get()->build_component(button_continue, camera_type::ORTHO));

	// Menu button
	auto button_menu = entity_manager::get()->create_entity("menu_button", state_type::PAUSE, menu_button_transform);
	button_menu->add_component("render", renderer::get()->build_component(button_menu, glm::vec4(0.0f, 0.0f,  0.0f, 1.0f), "res/textures/menu_button.png", "rectangle", "Gouraud", simple_texture));
	button_menu->add_component("clickable", clickable_system::get()->build_component(button_menu, glm::dvec2(0, 0 + button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_menu->add_component("camera", camera_system::get()->build_component(button_menu, camera_type::ORTHO));

	selection = pause_selection::continue_button;
}

void pause_state::on_reset()
{
	
}

void pause_state::on_enter()
{
    engine::get()->get_subsystem("clickable_system")->set_active(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//audio_system::get()->set_volume(0.70f);
	audio_system::get()->set_paused(true);
    std::cout << "Entered pause state, press ESC to go back to game state or BACKSPACE to go back to menu state" << std::endl;
}

void pause_state::on_update(float delta_time)
{
	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);
	entity_manager::get()->get_entity("pause")->get_trans().x = x_size / 2 - 100;
	entity_manager::get()->get_entity("pause")->get_trans().y = y_size - 50;

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	int count;
	const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	//std::cout << axes[10] << std::endl;
	static char up_old_axis = GLFW_RELEASE;

	// Handle input for up arrow
	static int up_old_state = GLFW_RELEASE;
	int up_state = glfwGetKey(glfw::window, GLFW_KEY_UP);

	if ((up_state == GLFW_RELEASE && up_old_state == GLFW_PRESS) || (present && axes[input_handler::get()->glfw_joystick_up] == GLFW_RELEASE && up_old_axis == GLFW_PRESS))
	{
		switch (selection)
		{
		case continue_button:
			selection = menu_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("menu_button"), "res/textures/menu_button_selected.png");
			// Set normal texture for other state
			renderer::get()->change_texture(entity_manager::get()->get_entity("continue_button"), "res/textures/continue_button.png");
			break;
		case menu_button:
			selection = continue_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("continue_button"), "res/textures/continue_button_selected.png");
			// Set normal texture for other state
			renderer::get()->change_texture(entity_manager::get()->get_entity("menu_button"), "res/textures/menu_button.png");
			break;
		}
		std::cout << selection << std::endl;
	}


	static char down_old_axis = GLFW_RELEASE;
	// Handle input for down arrow
	static int down_old_state = GLFW_RELEASE;
	int down_state = glfwGetKey(glfw::window, GLFW_KEY_DOWN);

	if ((down_state == GLFW_RELEASE && down_old_state == GLFW_PRESS) || (present && axes[input_handler::get()->glfw_joystick_down] == GLFW_RELEASE && down_old_axis == GLFW_PRESS))
	{

		switch (selection)
		{
		case menu_button:
			selection = continue_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("continue_button"), "res/textures/continue_button_selected.png");
			// Set normal texture for other state
			renderer::get()->change_texture(entity_manager::get()->get_entity("menu_button"), "res/textures/menu_button.png");
			break;
		case continue_button:
			selection = menu_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("menu_button"), "res/textures/menu_button_selected.png");
			// Set normal texture for other state
			renderer::get()->change_texture(entity_manager::get()->get_entity("continue_button"), "res/textures/continue_button.png");
			break;
		}
		std::cout << selection << std::endl;
	}

	static char enter_joystick_old_state = GLFW_RELEASE;
	static int enter_old_state = GLFW_RELEASE;
	int enter_state = glfwGetKey(glfw::window, GLFW_KEY_ENTER);
	if (enter_state == GLFW_RELEASE && enter_old_state == GLFW_PRESS || (present && axes[input_handler::get()->glfw_joystick_enter] == GLFW_RELEASE && enter_joystick_old_state == GLFW_PRESS))
	{
		switch (selection)
		{
		case continue_button:
			engine_state_machine::get()->change_state("game_state", false);
			break;
		case menu_button:
			engine_state_machine::get()->change_state("menu_state", true);
			break;
		}
	}
	enter_old_state = enter_state;
	down_old_state = down_state;
	up_old_state = up_state;
	if (present)
	{
		up_old_axis = axes[input_handler::get()->glfw_joystick_up];
		enter_joystick_old_state = axes[input_handler::get()->glfw_joystick_enter];
		down_old_axis = axes[input_handler::get()->glfw_joystick_down];
	}
}

void pause_state::on_exit()
{
    std::cout << "Exiting pause state" << std::endl;
}