#define GLM_ENABLE_EXPERIMENTAL
#include "settings_state.h"
#include "entity_manager.h"
#include <iostream>
#include "text2D.h"
#include <sstream>
#include <iomanip>
void settings_state::initialise()
{
	initText2D("res/textures/myriad.png");

	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	// Resolution transform
	transform_data resolution_transform;
	resolution_transform.x = 50;
	resolution_transform.y = y_size / 2;
	// Resolution
	auto resolution = entity_manager::get()->create_entity("Resolution", state_type::SETTINGS, resolution_transform);
	resolution->add_component("render", renderer::get()->build_component(resolution, "", "res/textures/play_button.png", "rectangle", "text", text));
	resolution->add_component("text", text_system::get()->build_component(resolution, "RESOLUTION"));

	// Resolution value transform
	transform_data resolution_value_transform;
	resolution_value_transform.x = resolution_transform.x + 350;
	resolution_value_transform.y = y_size / 2;
	// Resolution value
	std::stringstream streamx;
	streamx << std::fixed << std::setprecision(4) << x_size;
	std::string sx = streamx.str();
	std::stringstream streamy;
	streamy << std::fixed << std::setprecision(4) << y_size;
	std::string sy = streamy.str();
	std::cout << sx << " x " << sy << std::endl;
	auto resolution_value = entity_manager::get()->create_entity("ResolutionValue", state_type::SETTINGS, resolution_value_transform);
	resolution_value->add_component("render", renderer::get()->build_component(resolution_value, "", "res/textures/play_button.png", "rectangle", "text", text));
	resolution_value->add_component("text", text_system::get()->build_component(resolution_value, sx + " x " + sy));

	// Window mode transform
	transform_data window_transform;
	window_transform.x = 50;
	window_transform.y = (y_size / 2) - 50;
	// Window mode
	auto window_mode = entity_manager::get()->create_entity("WindowMode", state_type::SETTINGS, window_transform);
	window_mode->add_component("render", renderer::get()->build_component(window_mode, "", "res/textures/play_button.png", "rectangle", "text", text));
	window_mode->add_component("text", text_system::get()->build_component(window_mode, "WINDOW MODE"));

	// Title transform
	transform_data title_transform;
	title_transform.x = x_size / 2 - 200;
	title_transform.y = y_size - 250;
	// Title
	auto title = entity_manager::get()->create_entity("Title", state_type::SETTINGS, title_transform);
	title->add_component("render", renderer::get()->build_component(title, "", "res/textures/play_button.png", "rectangle", "text", text));
	title->add_component("text", text_system::get()->build_component(title, "SETTINGS"));
}

void settings_state::on_reset()
{

}

void settings_state::on_enter()
{
	// Switch off physics
	auto m = engine::get()->get_subsystem("entity_manager");
	// TODO: Should entity manager be enabled?
	engine::get()->get_subsystem("entity_manager")->set_active(true);
	engine::get()->get_subsystem("entity_manager")->set_visible(true);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	engine::get()->get_subsystem("clickable_system")->set_active(true);
	engine::get()->get_subsystem("renderer")->set_visible(true);
	engine::get()->get_subsystem("text_system")->set_active(true);

	glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	std::cout << "Entered settings state, press ENTER to go to game state" << std::endl;
}

void settings_state::on_update(float delta_time)
{
	//std::cout << "********** SETTINGS DISPLAYED ****************" << std::endl;
}

void settings_state::on_exit()
{
	std::cout << "Exiting settings state" << std::endl;
}