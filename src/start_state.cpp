#include "start_state.h"
#include <iostream>
void start_state::on_enter()
{
	std::cout << "Entered start state, press ANY key to go to MENU state" << std::endl;
}

void start_state::on_update(float delta_time)
{

}

void start_state::on_exit()
{
	std::cout << "Exiting start state" << std::endl;
}