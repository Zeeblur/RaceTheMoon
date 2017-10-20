//
// Created by zoe on 28/09/17.
//

#include <iostream>
#include "engine.h"
#include "entity_manager.h"
#include "systems/physics_system.h"
#include "renderer.h"
#include "state_machine.h"
#include "engine_state_machine.h"
#include "game_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "systems/input_handler.h"
#include "systems/clickable_system.h"
#include "systems/camera_system.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

using namespace std;
// Include GLM
#include <glm/glm.hpp>
using namespace glm;


int main() 
{
    std::cout << "hello world" << std::endl;

    auto eng = engine::get();
    eng->initWindowMan();
    eng->add_subsystem("entity_manager", entity_manager::get());
    eng->add_subsystem("physics_system", physics_system::get());
    eng->add_subsystem("renderer", renderer::get());
    eng->add_subsystem("state_machine", engine_state_machine::get());
    eng->add_subsystem("input_handler", input_handler::get());
	eng->add_subsystem("clickable_system", clickable_system::get());
	eng->add_subsystem("camera_system", camera_system::get());

    engine_state_machine::get()->add_state("menu_state", std::make_shared<menu_state>(), state_type::MENU);
    engine_state_machine::get()->add_state("game_state", std::make_shared<game_state>(), state_type::GAME);
    engine_state_machine::get()->add_state("pause_state", std::make_shared<pause_state>(), state_type::PAUSE);
    engine_state_machine::get()->change_state("game_state");


    // Adding plane
    auto p = entity_manager::get()->create_entity("Plane", state_type::GAME);
    p->add_component("physics", physics_system::get()->build_component(p));
    p->add_component("input", input_handler::get()->build_component(p));
    p->add_component("render", renderer::get()->build_component(p, "Red", "plane", "Gouraud", simple));

    // Adding cube
    auto c = entity_manager::get()->create_entity("Cube", state_type::GAME);
    c->add_component("physics", physics_system::get()->build_component(c));
    c->add_component("render", renderer::get()->build_component(c, "Green", "cube", "Gouraud", simple));

    // Bat entity
    auto e = entity_manager::get()->create_entity("Bat", state_type::GAME);
    e->add_component("physics", physics_system::get()->build_component(e));
    e->add_component("input", input_handler::get()->build_component(e));
    e->add_component("render", renderer::get()->build_component(e, "Blue", "res/models/bat.obj", "Gouraud", simple));
    e->add_component("camera", camera_system::get()->build_component(e, camera_type::CHASE));


    int x_size = 0;
    int y_size = 0;

    glfwGetWindowSize(glfw::window, &x_size, &y_size);

    int x_center = x_size / 2;
    int y_center = y_size / 2;

    int x_button_size = 100;
    int y_button_size = 50;
    // Y offset between buttons
    int button_offset = 100;
    // Menu buttons
    auto button_play = entity_manager::get()->create_entity("buttonPlay", state_type::MENU);
    button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
    button_play->add_component("render", renderer::get()->build_component(button_play, "Blue", "rectangle", "Gouraud", simple));

    auto button_exit = entity_manager::get()->create_entity("buttonExit", state_type::MENU);
    button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));

    // Pause buttons
    auto button_continue = entity_manager::get()->create_entity("buttonContinue", state_type::PAUSE);
    button_continue->add_component("clickable", clickable_system::get()->build_component(button_continue, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));

    auto button_menu = entity_manager::get()->create_entity("buttonMenu", state_type::PAUSE);
    button_menu->add_component("clickable", clickable_system::get()->build_component(button_menu, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(button_offset + y_center - y_button_size, button_offset + y_center + y_button_size)));

    eng->run();

    return 0;
}