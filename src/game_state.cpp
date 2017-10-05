#include "game_state.h"
#include <iostream>
void game_state::on_enter()
{
	// Turn on entities, physics, renderer
	engine::get()->get_subsystem("entity_manager")->set_active(true);
	engine::get()->get_subsystem("entity_manager")->set_visible(true);
	engine::get()->get_subsystem("physics_system")->set_active(true);
	engine::get()->get_subsystem("renderer")->set_visible(true);

	std::cout << "Entered game state" << std::endl;
}

void game_state::on_update(float delta_time)
{
	//std::cout << "**************** MAIN GAME RUNNING *****************" << std::endl;
}

void game_state::on_exit()
{
	std::cout << "Exiting game state" << std::endl;
}

