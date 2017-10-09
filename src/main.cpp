//
// Created by zoe on 28/09/17.
//

#include <iostream>
#include "engine.h"
#include "entity_manager.h"
#include "physics_system.h"
#include "renderer.h"
#include "state_machine.h"
#include "engine_states.h"
#include "input_handler.h"

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

    engine_state_machine::get()->add_state("1", std::make_shared<engine_state_1>());
    engine_state_machine::get()->add_state("2", std::make_shared<engine_state_2>());
    engine_state_machine::get()->change_state("2");

    auto e = entity_manager::get()->create_entity("Test");
    e->add_component("physics", physics_system::get()->build_component(e));
    e->add_component("render", renderer::get()->build_component(e, "Blue", "Sphere", "Gouraud", simple, "res/models/bat.obj"));

	eng->run();

    return 0;
}