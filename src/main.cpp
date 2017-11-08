//
// Created by zoe on 28/09/17.
//
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "engine.h"
#include "state_machine.h"
#include "engine_state_machine.h"
#include "game_state.h"
#include "menu_state.h"
#include "pause_state.h"

//#include <FreeImage-src\FreeImage.h>
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
	eng->add_subsystem("score_system", score_system::get());

    engine_state_machine::get()->add_state("menu_state", std::make_shared<menu_state>(), state_type::MENU);
    engine_state_machine::get()->add_state("game_state", std::make_shared<game_state>(), state_type::GAME);
    engine_state_machine::get()->add_state("pause_state", std::make_shared<pause_state>(), state_type::PAUSE);
    engine_state_machine::get()->change_state("game_state");
    eng->run();

    return 0;
}