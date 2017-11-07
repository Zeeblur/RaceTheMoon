//
// Created by zoe on 07/11/17.
//
#include "score_system.h"

score_system::score_system()
{
	_visible = false;
	_active = false;
}


bool score_system::initialise()
{
	return true;
}

bool score_system::load_content()
{
	std::cout << "Score system loading content" << std::endl;
	return true;
}

void score_system::update(float delta_time)
{
	std::cout << "reeee " << delta_time << std::endl;
}

void score_system::render()
{
	// This should never be called.
	std::cout << "Score system rendering" << std::endl;
}

void score_system::unload_content()
{
	std::cout << "Score system unloading content" << std::endl;
}

void score_system::shutdown()
{
	std::cout << "Score system shutting down" << std::endl;
}