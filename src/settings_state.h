#pragma once
#include "state_machine.h"

enum resolution 
{
	_1024x768,
	_1280x720,
	_1600x1200,
	_1920x1080,
};

enum window_mode
{
	windowed,
	fullscreen,
};

enum settings_selection
{
	resolution_button,
	window_mode_button
};

// Settings state
class settings_state : public engine_state
{
private:
	settings_selection selection;
public:


	resolution current_resolution = _1024x768;

	window_mode current_window_mode = windowed;

	void initialise();

	void on_reset();

	void on_enter();

	void on_update(float delta_time);

	void on_exit();
};

static int latest_key_press;