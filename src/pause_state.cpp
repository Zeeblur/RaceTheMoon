#include "pause_state.h"
#include "entity_manager.h"
#include "systems/clickable_system.h"
#include <iostream>

void pause_state::initialise()
{

}

void pause_state::on_reset()
{

}

void pause_state::on_enter()
{
    engine::get()->get_subsystem("clickable_system")->set_active(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    std::cout << "Entered pause state, press ESC to go back to game state or BACKSPACE to go back to menu state" << std::endl;
}

void pause_state::on_update(float delta_time)
{

}

void pause_state::on_exit()
{
    std::cout << "Exiting pause state" << std::endl;
}