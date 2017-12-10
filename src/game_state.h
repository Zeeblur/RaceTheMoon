#pragma once
#include "state_machine.h"
enum game_over_selection
{
	menu_button2 = 0,
	high_score_button = 1,
};
// Game state
class game_state : public engine_state
{
private:
	game_over_selection selection;
public:
	void initialise();

	void on_reset();

    void on_enter();

    void on_update(float delta_time);

    void on_exit();
};