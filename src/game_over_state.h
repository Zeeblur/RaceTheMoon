#pragma once
#include "state_machine.h"

// Game over state
class game_over_state : public engine_state
{
private:
	std::vector<std::string> high_scores;
	
public:

	void initialise();

	void display_high_scores();

	void on_reset();

	void on_enter();

	void on_update(float delta_time);

	void on_exit();
};
static std::vector<char> name;