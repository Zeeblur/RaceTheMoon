#pragma once
#include <iostream>
class engine_state
{
public:
	virtual ~engine_state() = default;

	virtual void on_enter() = 0;

	virtual void on_update(float delta_time) = 0;

	virtual void on_exit() = 0;
};