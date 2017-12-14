#pragma once
#include "state_machine.h"

enum pause_selection
{
	continue_button = 0,
	menu_button = 1,
};

// Pause state
class pause_state : public engine_state
{
private:
	pause_selection selection;

public:
	void initialise();

	void on_reset();

    void on_enter();

    void on_update(float delta_time);

    void on_exit();
};