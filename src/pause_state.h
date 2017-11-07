#pragma once
#include "state_machine.h"

// Pause state
class pause_state : public engine_state
{
public:
	void initialise();

    void on_enter();

    void on_update(float delta_time);

    void on_exit();
};