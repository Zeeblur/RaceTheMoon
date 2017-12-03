#pragma once
#include "state_machine.h"

enum resolution 
{
	_1024x768,
	_1280x720,
	_1600x1200,
	_1920x1080,
};

// Settings state
class settings_state : public engine_state
{
public:
	resolution current_resolution = _1024x768;

	void initialise();

	void on_reset();

	void on_enter();

	void on_update(float delta_time);

	void on_exit();
};