#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include <iostream>
#include "text2D.h"
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
	button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
	button_play->add_component("render", renderer::get()->build_component(button_play, "", "res/textures/play_button.png", "rectangle", "Gouraud", simple_texture));
	button_play->add_component("camera", camera_system::get()->build_component(button_play, camera_type::ORTHO));

	// Exit button
	auto button_exit = entity_manager::get()->create_entity("buttonExit", state_type::MENU, exit_button_transform);
	button_exit->add_component("render", renderer::get()->build_component(button_exit, "", "res/textures/exit_button.png", "rectangle", "Gouraud", simple_texture));
	button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));
	button_exit->add_component("camera", camera_system::get()->build_component(button_exit, camera_type::ORTHO));
	
	auto test = entity_manager::get()->create_entity("test1", state_type::MENU, exit_button_transform);
	test->add_component("render", renderer::get()->build_component(test, "", "res/textures/exit_button.png", "rectangle", "text", text));

	initText2D("res/textures/myriad.png");
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

    std::cout << "Entered menu state, press ENTER to go to game state" << std::endl;
}

void menu_state::on_update(float delta_time)
{
    //std::cout << "********** MENU DISPLAYED ****************" << std::endl;
}

void menu_state::on_exit()
{
    std::cout << "Exiting menu state" << std::endl;
}