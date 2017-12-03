#define GLM_ENABLE_EXPERIMENTAL
#include "game_over_state.h"
#include "entity_manager.h"
#include <iostream>

void game_over_state::initialise()
{
	
	transform_data game_over_texture_transform;
	game_over_texture_transform.scale = glm::vec3(1024, 768, 1.0f);
	auto background = entity_manager::get()->create_entity("buttonPlay", state_type::GAME_OVER, game_over_texture_transform);
	
	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/game_over_screen.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

}

void game_over_state::on_reset()
{

}

void game_over_state::on_enter()
{
	// Switch off entities, physics, renderer
	auto m = engine::get()->get_subsystem("entity_manager");
	// TODO: Should entity manager be enabled?
	//engine::get()->get_subsystem("entity_manager")->set_active(true);
	//engine::get()->get_subsystem("entity_manager")->set_visible(true);
	//engine::get()->get_subsystem("physics_system")->set_active(false);
	//engine::get()->get_subsystem("clickable_system")->set_active(true);
	//engine::get()->get_subsystem("input_handler")->set_active(false);
	//engine::get()->get_subsystem("renderer")->set_visible(true);

	glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	std::cout << "Entered game over state, press ANY BUTTON to go to game state" << std::endl;
}

void game_over_state::on_update(float delta_time)
{

}

void game_over_state::on_exit()
{
	std::cout << "Exiting game over state" << std::endl;
}