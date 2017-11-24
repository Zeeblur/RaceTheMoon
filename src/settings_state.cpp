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

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 2, y_size / 2, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::SETTINGS, back_transform);

	background->add_component("render", renderer::get()->build_component(background, "", "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

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

	// Buttons

	int x_center = x_size / 2;
	int y_center = y_size / 2;

	int x_button_size = 25;
	int y_button_size = 25;

	// right arrow trans
	transform_data right_arrow_transform;
	right_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	right_arrow_transform.x = resolution_transform.x + 300;
	right_arrow_transform.y = 120.0f;

	// left arrow trans
	transform_data left_arrow_transform;
	left_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	left_arrow_transform.x = resolution_transform.x - 100;
	left_arrow_transform.y = 120.0f;

	// Right arrow button
	auto button_right = entity_manager::get()->create_entity("buttonRight", state_type::SETTINGS, right_arrow_transform);
	//button_right->add_component("clickable", clickable_system::get()->build_component(button_right, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
	button_right->add_component("render", renderer::get()->build_component(button_right, "", "res/textures/arrow_right.png", "rectangle", "Gouraud", simple_texture));
	button_right->add_component("camera", camera_system::get()->build_component(button_right, camera_type::ORTHO));

	// Left arrow button
	auto button_left = entity_manager::get()->create_entity("buttonLeft", state_type::SETTINGS, left_arrow_transform);
	//button_left->add_component("clickable", clickable_system::get()->build_component(button_left, glm::vec2(x_center - x_button_size, x_center + x_button_size), glm::vec2(y_center - y_button_size, y_center + y_button_size)));
	button_left->add_component("render", renderer::get()->build_component(button_left, "", "res/textures/arrow_left.png", "rectangle", "Gouraud", simple_texture));
	button_left->add_component("camera", camera_system::get()->build_component(button_left, camera_type::ORTHO));

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