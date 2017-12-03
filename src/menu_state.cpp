#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include <iostream>
void menu_state::initialise()
{
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 1.25, y_size / 1.25, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::MENU, back_transform);

	background->add_component("render", renderer::get()->build_component(background, "", "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Menu text transform
	transform_data menu_transform;
	menu_transform.x = x_size / 2 - 220;
	menu_transform.y = y_size - 250;
	// Menu
	auto menu_text = entity_manager::get()->create_entity("mainMenu", state_type::MENU, menu_transform);
	menu_text->add_component("render", renderer::get()->build_component(menu_text, "", "res/textures/play_button.png", "rectangle", "text", text));
	menu_text->add_component("text", text_system::get()->build_component(menu_text, "MAIN MENU"));

	int x_button_size = 100;
	int y_button_size = 50;

	// Buttons transformations
	// Play button
	transform_data play_button_transform;
	play_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	play_button_transform.y = 125.0f;
	// Settings button
	transform_data settings_button_transform;
	settings_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	// Exit button
	transform_data exit_button_transform;
	exit_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	exit_button_transform.y = -125.0f;




	// Y offset between buttons
	int button_offset = 125;
	// Play button
	auto button_play = entity_manager::get()->create_entity("buttonPlay", state_type::MENU, play_button_transform);
	button_play->add_component("render", renderer::get()->build_component(button_play, "", "res/textures/play_button.png", "rectangle", "Gouraud", simple_texture));
	button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::dvec2(0, 0 - button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_play->add_component("camera", camera_system::get()->build_component(button_play, camera_type::ORTHO));

	// Settings button
	auto button_settings = entity_manager::get()->create_entity("buttonSettings", state_type::MENU, settings_button_transform);
	button_settings->add_component("render", renderer::get()->build_component(button_settings, "", "res/textures/play_button.png", "rectangle", "Gouraud", simple_texture));

	button_settings->add_component("clickable", clickable_system::get()->build_component(button_settings, glm::dvec2(0, 0), glm::dvec2(x_button_size, y_button_size)));
	button_settings->add_component("camera", camera_system::get()->build_component(button_settings, camera_type::ORTHO));

	// Exit button
	auto button_exit = entity_manager::get()->create_entity("buttonExit", state_type::MENU, exit_button_transform);
	button_exit->add_component("render", renderer::get()->build_component(button_exit, "", "res/textures/exit_button.png", "rectangle", "Gouraud", simple_texture));
	button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::dvec2(0, 0 + button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_exit->add_component("camera", camera_system::get()->build_component(button_exit, camera_type::ORTHO));
}

void menu_state::on_reset()
{

}

void menu_state::on_enter()
{
    // Switch off entities, physics, renderer
    auto m = engine::get()->get_subsystem("entity_manager");
    // TODO: Should entity manager be enabled?
    engine::get()->get_subsystem("entity_manager")->set_active(true);
    engine::get()->get_subsystem("entity_manager")->set_visible(true);
    engine::get()->get_subsystem("physics_system")->set_active(false);
    engine::get()->get_subsystem("clickable_system")->set_active(true);
    engine::get()->get_subsystem("renderer")->set_visible(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	audio_system::get()->stop_music();
	audio_system::get()->play_music(menu);

    std::cout << "Entered menu state, press ENTER to go to game state" << std::endl;
}

void menu_state::on_update(float delta_time)
{
	int x_size;
	int y_size;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);
	int button_offset = 125;
}

void menu_state::on_exit()
{
    std::cout << "Exiting menu state" << std::endl;
}