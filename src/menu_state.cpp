#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include <iostream>

void menu_state::initialise()
{
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	int x_center = x_size / 2;
	int y_center = y_size / 2;

	int x_button_size = 100;
	int y_button_size = 50;

	// button trans
	transform_data buttonTrans;
	buttonTrans.scale = glm::vec3(x_button_size, y_button_size, 1.0f);

	// Y offset between buttons
	int button_offset = 100;
	// Menu buttons
	auto button_play = entity_manager::get()->create_entity("buttonPlay", state_type::MENU, buttonTrans);
	button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
	button_play->add_component("render", renderer::get()->build_component(button_play, "Blue", "", "rectangle", "Gouraud", simple));
	button_play->add_component("camera", camera_system::get()->build_component(button_play, camera_type::ORTHO));

	auto button_exit = entity_manager::get()->create_entity("buttonExit", state_type::MENU);
	button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));

	// Pause buttons
	auto button_continue = entity_manager::get()->create_entity("buttonContinue", state_type::PAUSE);
	button_continue->add_component("clickable", clickable_system::get()->build_component(button_continue, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));

	auto button_menu = entity_manager::get()->create_entity("buttonMenu", state_type::PAUSE);
	button_menu->add_component("clickable", clickable_system::get()->build_component(button_menu, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));

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