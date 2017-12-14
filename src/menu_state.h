#pragma once
#include "state_machine.h"

enum menu_selection 
{
	play_button = 0,
	settings_button = 1,
	exit_button = 2
};

// Menu state
class menu_state : public engine_state
{
private:
	menu_selection selection;
public:
	void initialise();
	
	void on_reset();

    void on_enter();

    void on_update(float delta_time);

    void on_exit();
};