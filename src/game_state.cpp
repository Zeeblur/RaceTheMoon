#include "game_state.h"
#include "level_gen.h"
#include <iostream>
#include "text2D.h"
#include <iomanip>
#include <sstream>
#include <strstream>
#include <random>

void game_state::initialise()
{
	// Add background sphere
	transform_data sphTrans;
	sphTrans.scale = glm::vec3(1000.0f, 1000.0f, 1000.0f);
	auto sph = entity_manager::get()->create_entity("Sphere", this->type, sphTrans);
	sph->add_component("physics", physics_system::get()->build_component(sph));
	sph->add_component("render", renderer::get()->build_component(sph, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "", "sphere", "Gouraud", sky));


	// Adding plane
	auto p = entity_manager::get()->create_entity("Plane", this->type);
	p->add_component("physics", physics_system::get()->build_component(p));
	p->add_component("render", renderer::get()->build_component(p, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "res/textures/floor.jpg", "plane", "Gouraud", phongDistance));

    auto levelGenerator = level_gen::get();
	
	// initial setup 4 puzzles


    // Adding moon sphere
    transform_data moonTrans;
    moonTrans.scale = glm::vec3(10.0f, 10.0f, 10.0f);
    moonTrans.z = -1000.0f;
    auto m = entity_manager::get()->create_entity("Moon", this->type, moonTrans);
    m->add_component("physics", physics_system::get()->build_component(m));
	m->add_component("light", renderer::get()->build_light(m));
    m->add_component("ai", ai_system::get()->build_component(m, SUN_MOON, 0.0f, 0.0f));
	m->add_component("render", renderer::get()->build_component(m, glm::vec4(1.0f), "res/textures/sun.png", "sphere", "Gouraud", phong));


    // Adding sun sphere
    transform_data sunTrans;
    sunTrans.scale = glm::vec3(30.0f, 30.0f, 30.0f);
    sunTrans.y = -200.0f;
    sunTrans.z = -1000.0f;
    auto s = entity_manager::get()->create_entity("Sun", this->type, sunTrans);
    s->add_component("physics", physics_system::get()->build_component(s));
    s->add_component("ai", ai_system::get()->build_component(s, SUN_MOON, 0.0f, 0.0f));
    s->add_component("render", renderer::get()->build_component(s, glm::vec4(1.0f), "res/textures/sun.png", "sphere", "Gouraud", phong));



	transform_data batTrans;
	batTrans.y = 1.0f;
	batTrans.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	batTrans.rotation = glm::angleAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Bat entity
	auto e = entity_manager::get()->create_entity("Bat", this->type, batTrans);
	e->add_component("physics", physics_system::get()->build_component(e));
	e->add_component("input", input_handler::get()->build_component(e));
	e->add_component("render", renderer::get()->build_component(e, glm::vec4(0.5f, 0.2f, 0.05f, 1.0f), "res/textures/bat.jpg", "res/models/bat.obj", "Gouraud", phong));
	e->add_component("camera", camera_system::get()->build_component(e, camera_type::CHASE));
	e->add_component("collider", physics_system::get()->build_collider_component(e));
    e->add_component("score", score_system::get()->build_component(e));



	transform_data text_transform;
	text_transform.x = 10;
	text_transform.y = 10;
	auto test = entity_manager::get()->create_entity("test1", state_type::GAME, text_transform);
	test->add_component("render", renderer::get()->build_component(test, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	test->add_component("text", text_system::get()->build_component(test, "Score: 0"));

	transform_data text_transform2;
	text_transform2.x = 10;
	text_transform2.y = 100;
	auto test2 = entity_manager::get()->create_entity("test2", state_type::GAME, text_transform2);
	test2->add_component("render", renderer::get()->build_component(test2, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	test2->add_component("text", text_system::get()->build_component(test2, "Score: 0"));

	initText2D("res/textures/myriad.png");

}

void game_state::on_reset()
{
	auto bat = entity_manager::get()->get_entity("Bat");
	bat->get_component("physics")->initialise();

	for (auto d : physics_system::get()->_data)
	{
		d->reset_data();
	}

	// set score system active
	engine::get()->get_subsystem("score_system")->initialise();

	audio_system::get()->play_music(game);
}   

void game_state::on_enter()
{
    // Turn on entities, physics, renderer
    engine::get()->get_subsystem("entity_manager")->set_active(true);
    engine::get()->get_subsystem("entity_manager")->set_visible(true);
    engine::get()->get_subsystem("physics_system")->set_active(true);
    engine::get()->get_subsystem("renderer")->set_visible(true);
    engine::get()->get_subsystem("clickable_system")->set_active(false);
	engine::get()->get_subsystem("level_gen")->set_active(true);
	// set to zero
	audio_system::get()->set_volume(0.0f);
	// set score system active
	engine::get()->get_subsystem("score_system")->set_active(true);

    glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	audio_system::get()->set_paused(false);
    std::cout << "Entered game state, press ESC to go to pause state" << std::endl;
}

void game_state::on_update(float delta_time)
{
	static float total_time;
	total_time += delta_time;
	//std::shared_ptr<text_system> ts = std::dynamic_pointer_cast<text_system>(engine::get()->get_subsystem("text_system"));
	std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("test1")->get_component("text"));
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << total_time;
	std::string s = stream.str();
	tc->_data->text = s;

	std::shared_ptr<text_component> tc2 = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("test2")->get_component("text"));
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(2) << total_time;
	std::string s2 = stream2.str();
	tc2->_data->text = s2;

}

void game_state::on_exit()
{
    std::cout << "Exiting game state" << std::endl;

	// set score system to false
	engine::get()->get_subsystem("score_system")->set_active(false);
}

