#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include <iostream>
void menu_state::initialise()
{
	// TODO: Fix button click event problem when changing window size.

	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	int x_center = x_size / 2;
	int y_center = y_size / 2;

	int x_button_size = 100;
	int y_button_size = 50;

	// button trans
	transform_data play_button_transform;
	play_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);

	play_button_transform.y = 0.0f;
	transform_data exit_button_transform;
	exit_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	exit_button_transform.y = -125.0f;

	// Y offset between buttons
	int button_offset = 125;
	// Play button
	auto button_play = entity_manager::get()->create_entity("buttonPlay", state_type::MENU, play_button_transform);
	std::shared_ptr<clickable_component> play_clickable = clickable_system::get()->build_component(button_play, glm::dvec2(x_center, y_center), glm::dvec2(x_button_size, y_button_size));
	button_play->add_component("clickable", play_clickable);
	button_play->add_component("render", renderer::get()->build_component(button_play, "", "res/textures/play_button.png", "rectangle", "Gouraud", simple_texture));
	button_play->add_component("camera", camera_system::get()->build_component(button_play, camera_type::ORTHO));

	// Exit button
	auto button_exit = entity_manager::get()->create_entity("buttonExit", state_type::MENU, exit_button_transform);
	button_exit->add_component("render", renderer::get()->build_component(button_exit, "", "res/textures/exit_button.png", "rectangle", "Gouraud", simple_texture));
	std::shared_ptr<clickable_component> exit_clickable = clickable_system::get()->build_component(button_exit, glm::dvec2(x_center, y_center + button_offset ), glm::dvec2(x_button_size, y_button_size));
	button_exit->add_component("clickable", exit_clickable);
	button_exit->add_component("camera", camera_system::get()->build_component(button_exit, camera_type::ORTHO));

	clickable_components.push_back(play_clickable);
	clickable_components.push_back(exit_clickable);
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
	// TODO: Add some sort of window size changed event and then update center value
	int x_size;
	int y_size;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);
	int button_offset = 125;

	clickable_components[0].get()->_data.center.x = x_size / 2;
	clickable_components[0].get()->_data.center.y = y_size / 2;

	clickable_components[1].get()->_data.center.x = x_size / 2;
	clickable_components[1].get()->_data.center.y = y_size / 2 + 125;
	//std::cout << "********** MENU DISPLAYED ******;**********" << std::endl;
}

void menu_state::on_exit()
{
    std::cout << "Exiting menu state" << std::endl;
}