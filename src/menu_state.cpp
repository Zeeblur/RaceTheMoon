#include "menu_state.h"
#include "entity_manager.h"
#include "clickable_system.h"
#include <iostream>
void menu_state::on_enter()
{
	// Switch off entities, physics, renderer
	auto m = engine::get()->get_subsystem("entity_manager");
	// TODO: Should entity manager be enabled?
	engine::get()->get_subsystem("entity_manager")->set_active(false);
	engine::get()->get_subsystem("entity_manager")->set_visible(false);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	engine::get()->get_subsystem("clickable_system")->set_active(true);

	// Set up buttons only once
	if (!_initialised)
	{
		int x_size = 0;
		int y_size = 0;

		glfwGetWindowSize(glfw::window, &x_size, &y_size);

		int x_center = x_size / 2;
		int y_center = y_size / 2;

		int x_button_size = 100;
		int y_button_size = 50;
		// Y offset between buttons
		int button_offset = 100;

		auto button_play = entity_manager::get()->create_entity("buttonPlay");
		button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
		//_buttons.push_back(button_play.get());
		auto button_exit = entity_manager::get()->create_entity("buttonExit");
		button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));
		//_buttons.push_back(button_exit.get());
		_initialised = true;
	}
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