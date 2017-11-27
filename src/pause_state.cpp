#include "pause_state.h"
#include "entity_manager.h"
#include "systems/clickable_system.h"
#include <iostream>

void pause_state::initialise()
{
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	// Pause text transform
	transform_data paused_transform;
	paused_transform.x = x_size / 2 - 175;
	paused_transform.y = y_size - 250;
	// Pause
	auto paused_text = entity_manager::get()->create_entity("pause", state_type::PAUSE, paused_transform);
	paused_text->add_component("render", renderer::get()->build_component(paused_text, "", "res/textures/play_button.png", "rectangle", "text", text));
	paused_text->add_component("text", text_system::get()->build_component(paused_text, "PAUSED"));

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 1.25, y_size / 1.25, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::PAUSE, back_transform);

	background->add_component("render", renderer::get()->build_component(background, "", "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
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
	auto button_continue = entity_manager::get()->create_entity("buttonContinue", state_type::PAUSE, continue_button_transform);
	button_continue->add_component("render", renderer::get()->build_component(button_continue, "", "res/textures/continue_button.png", "rectangle", "Gouraud", simple_texture));
	button_continue->add_component("clickable", clickable_system::get()->build_component(button_continue, glm::dvec2(0, 0), glm::dvec2(x_button_size, y_button_size)));
	button_continue->add_component("camera", camera_system::get()->build_component(button_continue, camera_type::ORTHO));

	// Menu button
	auto button_menu = entity_manager::get()->create_entity("buttonMenu", state_type::PAUSE, menu_button_transform);
	button_menu->add_component("render", renderer::get()->build_component(button_menu, "", "res/textures/menu_button.png", "rectangle", "Gouraud", simple_texture));
	button_menu->add_component("clickable", clickable_system::get()->build_component(button_menu, glm::dvec2(0, 0 + button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_menu->add_component("camera", camera_system::get()->build_component(button_menu, camera_type::ORTHO));
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

}

void pause_state::on_exit()
{
    std::cout << "Exiting pause state" << std::endl;
}