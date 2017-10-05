#include "menu_state.h"
#include <iostream>
void menu_state::on_enter()
{
	// Switch off entities, physics, renderer
	auto m = engine::get()->get_subsystem("entity_manager");
	engine::get()->get_subsystem("entity_manager")->set_active(false);
	engine::get()->get_subsystem("entity_manager")->set_visible(false);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	//engine::get()->get_subsystem("renderer")->set_visible(false);

	std::cout << "Entered menu state" << std::endl;
}

void menu_state::on_update(float delta_time)
{
	//std::cout << "********** MENU DISPLAYED ****************" << std::endl;
}

void menu_state::on_exit()
{
	std::cout << "Exiting menu state" << std::endl;
}