#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include "systems/clickable_system.h"
#include "renderer.h"
#include <iostream>

void menu_state::on_enter()
{
    // Switch off entities, physics, renderer
    auto m = engine::get()->get_subsystem("entity_manager");
    // TODO: Should entity manager be enabled?
    engine::get()->get_subsystem("entity_manager")->set_active(true);
    engine::get()->get_subsystem("entity_manager")->set_visible(true);
    engine::get()->get_subsystem("physics_system")->set_active(false);
    engine::get()->get_subsystem("clickable_system")->set_active(true);
    engine::get()->get_subsystem("renderer")->set_visible(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    std::cout << "Entered menu state, press ENTER to go to game state" << std::endl;
}

void menu_state::on_update(float delta_time)
{


    //std::cout << "********** MENU DISPLAYED ****************" << std::endl;
}

void menu_state::on_exit()
{
    std::cout << "Exiting menu state" << std::endl;
}