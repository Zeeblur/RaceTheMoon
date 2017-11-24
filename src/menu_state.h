#pragma once
#include "state_machine.h"
// Menu state
class menu_state : public engine_state
{
private:
	std::vector<std::shared_ptr<clickable_component>> clickable_components;
public:
	void initialise();
	
	void on_reset();

    void on_enter();

    void on_update(float delta_time);

    void on_exit();
};