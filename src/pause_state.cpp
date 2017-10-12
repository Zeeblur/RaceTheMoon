#include "pause_state.h"
#include <iostream>
void pause_state::on_enter()
{
	std::cout << "Entered pause state, press ESC to go back to game state or BACKSPACE to go back to menu state" << std::endl;
}

void pause_state::on_update(float delta_time)
{

}

void pause_state::on_exit()
{
	std::cout << "Exiting pause state" << std::endl;
}