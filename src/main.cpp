//
// Created by zoe on 28/09/17.
//

#include <iostream>
#include "engine.h"
#include "entity_manager.h"
#include "physics_system.h"
#include "renderer.h"
#include "state_machine.h"
#include "engine_state_machine.h"
#include "game_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "input_handler.h"
#include "clickable_system.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

using namespace std;
// Include GLM
#include <glm/glm.hpp>
using namespace glm;


int main() {

    std::cout << "hello world" << std::endl;

    auto eng = engine::get();
	eng->initWindowMan();
    eng->add_subsystem("entity_manager", entity_manager::get());
    eng->add_subsystem("physics_system", physics_system::get());
    eng->add_subsystem("renderer", renderer::get());
    eng->add_subsystem("state_machine", engine_state_machine::get());
    eng->add_subsystem("input_handler", input_handler::get());
	eng->add_subsystem("clickable_system", clickable_system::get());

    engine_state_machine::get()->add_state("menu_state", std::make_shared<menu_state>(), state_type::MENU);
    engine_state_machine::get()->add_state("game_state", std::make_shared<game_state>(), state_type::GAME);
	engine_state_machine::get()->add_state("pause_state", std::make_shared<pause_state>(), state_type::PAUSE);
    engine_state_machine::get()->change_state("game_state");

    auto e = entity_manager::get()->create_entity("Test");
    e->add_component("physics", physics_system::get()->build_component(e));
    e->add_component("render", renderer::get()->build_component(e, "Blue", "Sphere", "Gouraud", simple, "res/models/bat.obj"));

	auto buttonEntity = entity_manager::get()->create_entity("Button");
	buttonEntity->add_component("clickable", clickable_system::get()->build_component(buttonEntity, glm::vec2(0,200), glm::vec2(0,200)));


	eng->run();

    return 0;
}