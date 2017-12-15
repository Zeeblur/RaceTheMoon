#pragma once
#include "state_machine.h"

enum controls_selection
{
	move_left_button,
	move_right_button,
	enter_joystick_button,
	controls_back_button
};

// Settings state
class controls_state : public engine_state
{
private:
	controls_selection selection;
public:
	//int left_move_key = -1;
	//int right_move_key = -1;

	void initialise();

	void on_reset();

	void on_enter();

	void on_update(float delta_time);

	void on_exit();
};

static int latest_key_press;