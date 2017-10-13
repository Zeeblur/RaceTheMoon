#pragma once
#include <iostream>

enum state_type
{
    START,
    MENU,
    GAME,
    PAUSE,
    OPTIONS,
    EXIT,
    NONE
};

class engine_state
{

public:
    state_type type;

    virtual ~engine_state() = default;

    virtual void on_enter() = 0;

    virtual void on_update(float delta_time) = 0;

    virtual void on_exit() = 0;
};