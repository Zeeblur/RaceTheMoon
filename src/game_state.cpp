#include "game_state.h"
#include <iostream>


void game_state::initialise()
{

	// can add a transformation in using struct now
	auto light = entity_manager::get()->create_entity("Light", this->type);
	light->add_component("light", renderer::get()->build_light(light));

	// Adding plane
	auto p = entity_manager::get()->create_entity("Plane", this->type);
	p->add_component("physics", physics_system::get()->build_component(p));
	p->add_component("render", renderer::get()->build_component(p, "Red", "", "plane", "Gouraud", simple));

	transform_data cubeTrans;
	cubeTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	cubeTrans.x = -20.0f;
	//cubeTrans.y = 1.0f;
	cubeTrans.z = -20.0f;
	// Adding cube
	auto c = entity_manager::get()->create_entity("Cube", this->type, cubeTrans);
	c->add_component("physics", physics_system::get()->build_component(c));
	c->add_component("render", renderer::get()->build_component(c, "Green", "res/textures/check.jpg", "cube", "Gouraud", phong));

    // Adding moon sphere
    transform_data moonTrans;
    moonTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
    moonTrans.z = -1000.0f;
    auto m = entity_manager::get()->create_entity("Moon", this->type, moonTrans);
    m->add_component("physics", physics_system::get()->build_component(m));
    m->add_component("input", input_handler::get()->build_ai_component(m));
    m->add_component("render", renderer::get()->build_component(m, "White", "res/textures/check.jpg", "sphere", "Gouraud", phong));

	//c->add_component("collider", physics_system::get()->build_collider_component(c, cubeTrans.scale));

	transform_data batTrans;
	batTrans.y = 5.0f;
	batTrans.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	batTrans.rotation = glm::angleAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Bat entity
	auto e = entity_manager::get()->create_entity("Bat", this->type, batTrans);
	e->add_component("physics", physics_system::get()->build_component(e));
	e->add_component("input", input_handler::get()->build_component(e));
	e->add_component("render", renderer::get()->build_component(e, "Blue", "res/textures/bat.jpg", "res/models/bat.obj", "Gouraud", phong));
	e->add_component("camera", camera_system::get()->build_component(e, camera_type::CHASE));
	//e->add_component("collider", physics_system::get()->build_collider_component(e, batTrans.scale * 5.0f));

}

void game_state::on_enter()
{
    // Turn on entities, physics, renderer
    engine::get()->get_subsystem("entity_manager")->set_active(true);
    engine::get()->get_subsystem("entity_manager")->set_visible(true);
    engine::get()->get_subsystem("physics_system")->set_active(true);
    engine::get()->get_subsystem("renderer")->set_visible(true);
    engine::get()->get_subsystem("clickable_system")->set_active(false);
	
	// set score system active
	engine::get()->get_subsystem("score_system")->set_active(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    std::cout << "Entered game state, press ESC to go to pause state" << std::endl;
}

void game_state::on_update(float delta_time)
{
    //std::cout << "**************** MAIN GAME RUNNING *****************" << std::endl;
}

void game_state::on_exit()
{
    std::cout << "Exiting game state" << std::endl;

	// set score system to false
	engine::get()->get_subsystem("score_system")->set_active(false);
}

