#define GLM_ENABLE_EXPERIMENTAL
#include "menu_state.h"
#include "entity_manager.h"
#include "engine_state_machine.h"
#include <iostream>
void menu_state::initialise()
{
	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size * 0.5, y_size * 0.5, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::MENU, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Menu text transform
	transform_data menu_transform;
	menu_transform.x = x_size / 2 - 220;
	menu_transform.y = y_size - 250;
	// Menu
	auto menu_text = entity_manager::get()->create_entity("mainMenu", state_type::MENU, menu_transform);
	menu_text->add_component("render", renderer::get()->build_component(menu_text, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	menu_text->add_component("text", text_system::get()->build_component(menu_text, "MAIN MENU"));

	int x_button_size = 100;
	int y_button_size = 50;

	// Buttons transformations
	// Play button
	transform_data play_button_transform;
	play_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	play_button_transform.y = 125.0f;
	// Settings button
	transform_data settings_button_transform;
	settings_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	// Exit button
	transform_data exit_button_transform;
	exit_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	exit_button_transform.y = -125.0f;


	// Y offset between buttons
	int button_offset = 125;
	// Play button
	auto button_play = entity_manager::get()->create_entity("play_button", state_type::MENU, play_button_transform);
	button_play->add_component("render", renderer::get()->build_component(button_play, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button_selected.png", "rectangle", "Gouraud", simple_texture));
	button_play->add_component("clickable", clickable_system::get()->build_component(button_play, glm::dvec2(0, 0 - button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_play->add_component("camera", camera_system::get()->build_component(button_play, camera_type::ORTHO));

	// Settings button
	auto button_settings = entity_manager::get()->create_entity("settings_button", state_type::MENU, settings_button_transform);
	button_settings->add_component("render", renderer::get()->build_component(button_settings, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/settings_button.png", "rectangle", "Gouraud", simple_texture));
	button_settings->add_component("clickable", clickable_system::get()->build_component(button_settings, glm::dvec2(0, 0), glm::dvec2(x_button_size, y_button_size)));
	button_settings->add_component("camera", camera_system::get()->build_component(button_settings, camera_type::ORTHO));

	// Exit button
	auto button_exit = entity_manager::get()->create_entity("exit_button", state_type::MENU, exit_button_transform);
	button_exit->add_component("render", renderer::get()->build_component(button_exit, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "Gouraud", simple_texture));
	button_exit->add_component("clickable", clickable_system::get()->build_component(button_exit, glm::dvec2(0, 0 + button_offset), glm::dvec2(x_button_size, y_button_size)));
	button_exit->add_component("camera", camera_system::get()->build_component(button_exit, camera_type::ORTHO));

	// Default to play button
	selection = menu_selection::play_button;
}

void menu_state::on_reset()
{

}

void menu_state::on_enter()
{
	// Switch off entities, physics, renderer
	auto m = engine::get()->get_subsystem("entity_manager");

	engine::get()->get_subsystem("entity_manager")->set_active(true);
	engine::get()->get_subsystem("entity_manager")->set_visible(true);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	engine::get()->get_subsystem("clickable_system")->set_active(true);
	engine::get()->get_subsystem("renderer")->set_visible(true);

	glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	audio_system::get()->stop_music();
	audio_system::get()->play_music(menu);

	std::cout << "Entered menu state, press ENTER to go to game state" << std::endl;
}

void menu_state::on_update(float delta_time)
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	int count;
	const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	//std::cout << axes[10] << std::endl;
	static char up_old_axis = GLFW_RELEASE;

	// Handle input for up arrow
	static int up_old_state = GLFW_RELEASE;
	int up_state = glfwGetKey(glfw::window, GLFW_KEY_UP);

	if ((up_state == GLFW_RELEASE && up_old_state == GLFW_PRESS) || (present && axes[10] == GLFW_RELEASE && up_old_axis == GLFW_PRESS))
	{
		switch (selection)
		{
		case play_button:
			selection = exit_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button.png");
			break;
		case settings_button:
			selection = play_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button.png");
			break;
		case exit_button:
			selection = settings_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button.png");
			break;
		}
		std::cout << selection << std::endl;
	}
	

	static char down_old_axis = GLFW_RELEASE;
	// Handle input for down arrow
	static int down_old_state = GLFW_RELEASE;
	int down_state = glfwGetKey(glfw::window, GLFW_KEY_DOWN);

	if ((down_state == GLFW_RELEASE && down_old_state == GLFW_PRESS) || (present && axes[12] == GLFW_RELEASE && down_old_axis == GLFW_PRESS))
	{

		switch (selection)
		{
		case play_button:
			selection = settings_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button.png");
			break;
		case settings_button:
			selection = exit_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button.png");
			break;
		case exit_button:
			selection = play_button;
			// Set selected texture
			renderer::get()->change_texture(entity_manager::get()->get_entity("play_button"), "res/textures/play_button_selected.png");
			// Set normal texture for other two states
			renderer::get()->change_texture(entity_manager::get()->get_entity("settings_button"), "res/textures/settings_button.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("exit_button"), "res/textures/exit_button.png");
			break;
		}
		std::cout << selection << std::endl;
	}


	static char enter_joystick_old_state = GLFW_RELEASE;
	static int enter_old_state = GLFW_RELEASE;
	int enter_state = glfwGetKey(glfw::window, GLFW_KEY_ENTER);
	if (enter_state == GLFW_RELEASE && enter_old_state == GLFW_PRESS || (present && axes[0] == GLFW_RELEASE && enter_joystick_old_state == GLFW_PRESS))
	{
		switch (selection)
		{
		case play_button:
			engine_state_machine::get()->change_state("game_state", true);
			break;
		case settings_button:
			engine_state_machine::get()->change_state("settings_state", true);
			break;
		case exit_button:
			// Handle exit game logic here
			engine::get()->set_running(false);
			break;
		}
	}
	up_old_state = up_state;
	down_old_state = down_state;
	enter_old_state = enter_state;

	if (present)
	{
		up_old_axis = axes[10];
		down_old_axis = axes[12];
		enter_joystick_old_state = axes[0];
	}
	
}

void menu_state::on_exit()
{
	std::cout << "Exiting menu state" << std::endl;
}