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

    //For loop for scenery repetition
    /*for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        bad_map(i, j);
    }*/

     //Adding cube 1
    transform_data cubeTrans;
    cubeTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
    cubeTrans.x = -20.0f;
    cubeTrans.y = 5.0f;
    cubeTrans.z = -20.0f;
    auto c = entity_manager::get()->create_entity("Cube", this->type, cubeTrans);
    c->add_component("physics", physics_system::get()->build_component(c));
    c->add_component("render", renderer::get()->build_component(c, "Green", "res/textures/check.jpg", "cube", "Gouraud", phong));
    // Adding cube 2
    transform_data cube2Trans;
    cube2Trans.scale = glm::vec3(10.0f, 30.0f, 10.0f);
    cube2Trans.x = 20.0f;
    cube2Trans.y = 5.0f;
    cube2Trans.z = -20.0f;
    auto c2 = entity_manager::get()->create_entity("Cube2", this->type, cube2Trans);
    c2->add_component("physics", physics_system::get()->build_component(c2));
    c2->add_component("render", renderer::get()->build_component(c2, "Green", "", "cube", "Gouraud", phong));
    // Adding cube 3
    transform_data cube3Trans;
    cube3Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    cube3Trans.x = 20.0f;
    cube3Trans.y = 5.0f;
    cube3Trans.z = -120.0f;
    auto c3 = entity_manager::get()->create_entity("Cube3", this->type, cube3Trans);
    c3->add_component("physics", physics_system::get()->build_component(c3));
    c3->add_component("render", renderer::get()->build_component(c3, "Green", "res/textures/stone.jpg", "cube", "Gouraud", phong));
    // Adding cube 4
    transform_data cube4Trans;
    cube4Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    cube4Trans.x = -20.0f;
    cube4Trans.y = 5.0f;
    cube4Trans.z = -120.0f;
    auto c4 = entity_manager::get()->create_entity("Cube4", this->type, cube4Trans);
    c4->add_component("physics", physics_system::get()->build_component(c4));
    c4->add_component("render", renderer::get()->build_component(c4, "Green", "res/textures/moon.png", "cube", "Gouraud", phong));

    // Adding moon sphere
    transform_data moonTrans;
    moonTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
    moonTrans.z = -1000.0f;
    auto m = entity_manager::get()->create_entity("Moon", this->type, moonTrans);
    m->add_component("physics", physics_system::get()->build_component(m));
    m->add_component("input", ai_system::get()->build_component(m, 0, glm::vec3(0.0f, 10.0f, 0.0f)));
    m->add_component("render", renderer::get()->build_component(m, "White", "res/textures/moon.png", "sphere", "Gouraud", phong));

    // Adding sun sphere
    transform_data sunTrans;
    sunTrans.scale = glm::vec3(30.0f, 30.0f, 30.0f);
    sunTrans.z = -1000.0f;
    sunTrans.y = -200.0f;
    auto s = entity_manager::get()->create_entity("Sun", this->type, sunTrans);
    s->add_component("physics", physics_system::get()->build_component(s));
    s->add_component("input", ai_system::get()->build_component(s, 0, glm::vec3(0.0f, 10.0f, 0.0f)));
    s->add_component("render", renderer::get()->build_component(s, "White", "res/textures/sun.png", "sphere", "Gouraud", phong));

	c->add_component("collider", physics_system::get()->build_collider_component(c));

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
	e->add_component("collider", physics_system::get()->build_collider_component(e));

}

// ** attempt at repeating scenery.. it's crap don't worry **
//void game_state::bad_map(int iter, int iter2)
//{
//    // Adding cube 1
//    transform_data cubeTrans;
//    cubeTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
//    cubeTrans.scale *= iter *= iter2;
//    cubeTrans.x = -20.0f * iter * iter2;
//    cubeTrans.z = -20.0f * iter * iter2;
//    auto c = entity_manager::get()->create_entity("Cube", this->type, cubeTrans);
//    c->add_component("physics", physics_system::get()->build_component(c));
//    c->add_component("render", renderer::get()->build_component(c, "Green", "res/textures/check.jpg", "cube", "Gouraud", phong));
//    // Adding cube 2
//    transform_data cube2Trans;
//    cube2Trans.scale = glm::vec3(10.0f, 30.0f, 10.0f);
//    cube2Trans.scale *= iter *= iter2;
//    cube2Trans.x = 20.0f * iter * iter2;
//    cube2Trans.z = -20.0f * iter * iter2;
//    auto c2 = entity_manager::get()->create_entity("Cube2", this->type, cube2Trans);
//    c2->add_component("physics", physics_system::get()->build_component(c2));
//    c2->add_component("render", renderer::get()->build_component(c2, "Green", "", "cube", "Gouraud", phong));
//    // Adding cube 3
//    transform_data cube3Trans;
//    cube3Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
//    cube3Trans.scale *= iter *= iter2;
//    cube3Trans.x = 20.0f * iter * iter2;
//    cube3Trans.z = -120.0f * iter * iter2;
//    auto c3 = entity_manager::get()->create_entity("Cube3", this->type, cube3Trans);
//    c3->add_component("physics", physics_system::get()->build_component(c3));
//    c3->add_component("render", renderer::get()->build_component(c3, "Green", "res/textures/stone.jpg", "cube", "Gouraud", phong));
//    // Adding cube 4
//    transform_data cube4Trans;
//    cube4Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
//    cube4Trans.scale *= iter *= iter2;
//    cube4Trans.x = -20.0f * iter * iter2;
//    cube4Trans.z = -120.0f * iter * iter2;
//    auto c4 = entity_manager::get()->create_entity("Cube4", this->type, cube4Trans);
//    c4->add_component("physics", physics_system::get()->build_component(c4));
//    c4->add_component("render", renderer::get()->build_component(c4, "Green", "res/textures/moon.png", "cube", "Gouraud", phong));
//}

void game_state::on_reset()
{
	auto bat = entity_manager::get()->get_entity("Bat");
	bat->get_component("physics")->initialise();

	// set score system active
	engine::get()->get_subsystem("score_system")->initialise();
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

