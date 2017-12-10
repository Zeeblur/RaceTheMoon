//
// Created by zoe on 07/11/17.
//
#include "score_system.h"
#include "../engine_state_machine.h"

score_system::score_system()
{
	_visible = false;
	_active = false;
}

std::shared_ptr<score_component> score_system::build_component(std::shared_ptr<entity> e)
{
	auto sd = std::make_shared<score_data>(score_data());

	_data.push_back(sd);
	return std::make_shared<score_component>(e, sd);
}

bool score_system::initialise()
{
	totalTime = 0;
	seconds = 0;

	return true;
}

bool score_system::load_content()
{
	std::cout << "Score system loading content" << std::endl;
	return true;
}

void score_system::hurt()
{
	// ouch
	for(auto &d : _data)
	{
		d->health -= 10;

		if (d->health <= 0)
		{
			//stop game
			engine_state_machine::get()->change_state("game_over_state", true);
			std::cout << "You died!!! score= " << seconds + d->score << std::endl;
			//d->score = 0;
			d->health = 110;
		}
	}

}

void score_system::addScore()
{
	for(auto &d : _data)
	{
		d->score++;
	}
}

void score_system::addPointsPowerUp()
{
    for (auto &d : _data)
    {
        d->score += 100;
    }
}

void score_system::update(float delta_time)
{
	totalTime += (delta_time);

	seconds = fmod(totalTime, 1000);

	for (auto &s : _data)
	{
		s->score += seconds;
		std::cout << "Time is now: " << seconds << std::endl;
		std::cout << "Score is now: " << s->score << std::endl;
		std::cout << "Health : " << s->health << std::endl;
	}
	//std::cout << "reeee " << seconds << std::endl;
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