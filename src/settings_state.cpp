#define GLM_ENABLE_EXPERIMENTAL
#include "settings_state.h"
#include "entity_manager.h"
#include <iostream>
#include "text2D.h"
#include <sstream>
#include <iomanip>
#include <fstream>
#include "engine_state_machine.h"
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//latest_key_press = -1;

	if (action == GLFW_PRESS)
	{
		latest_key_press = key;
		std::cout << "pressed" << std::endl;
		std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("help_text")->get_component("text"));
		tc->_data->text = " ";
	}
}

void key_callback_fake(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	latest_key_press = -1;
}

void settings_state::initialise()
{

	latest_key_press = -1;

	initText2D("res/textures/myriad.png");

	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 1.25, y_size / 1.25, 1.0f);
	back_transform.z = -10;
	auto background = entity_manager::get()->create_entity("background", state_type::SETTINGS, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Back button transform
	transform_data back_button_transform;
	back_button_transform.x = 0;
	back_button_transform.y = -270;
	back_button_transform.scale.x = 100;
	back_button_transform.scale.y = 50;
	// Back button
	auto back_button = entity_manager::get()->create_entity("back_button", state_type::SETTINGS, back_button_transform);
	back_button->add_component("render", renderer::get()->build_component(back_button, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/back_button.png", "rectangle", "Gouraud", simple_texture));
	back_button->add_component("camera", camera_system::get()->build_component(back_button, camera_type::ORTHO));
	back_button->add_component("clickable", clickable_system::get()->build_component(back_button, vec2(back_button_transform.x, -back_button_transform.y), back_button_transform.scale));

	// Resolution value transform
	transform_data resolution_value_transform;
	resolution_value_transform.x = 0;
	resolution_value_transform.y = 180;
	resolution_value_transform.scale.x = 100;
	resolution_value_transform.scale.y = 30;
	// Resolution value
	auto resolution_value = entity_manager::get()->create_entity("resolutionValue", state_type::SETTINGS, resolution_value_transform);
	resolution_value->add_component("render", renderer::get()->build_component(resolution_value, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/1024x768.png", "rectangle", "Gouraud", simple_texture));
	resolution_value->add_component("camera", camera_system::get()->build_component(resolution_value, camera_type::ORTHO));

	// Resolution transform
	transform_data resolution_transform;
	resolution_transform.x = 0;
	resolution_transform.y = 240;
	resolution_transform.scale.x = 100;
	resolution_transform.scale.y = 30;
	// Resolution
	auto resolution = entity_manager::get()->create_entity("Resolution", state_type::SETTINGS, resolution_transform);
	resolution->add_component("render", renderer::get()->build_component(resolution, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/resolution.png", "rectangle", "Gouraud", simple_texture));
	resolution->add_component("camera", camera_system::get()->build_component(resolution, camera_type::ORTHO));

	// Window mode value transform
	transform_data window_mode_value_transform;
	window_mode_value_transform.x = 0;
	window_mode_value_transform.y = 60;
	window_mode_value_transform.scale.x = 100;
	window_mode_value_transform.scale.y = 30;
	// Window mode value
	auto window_mode_value = entity_manager::get()->create_entity("windowModeValue", state_type::SETTINGS, window_mode_value_transform);
	window_mode_value->add_component("render", renderer::get()->build_component(window_mode_value, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/fullscreen.png", "rectangle", "Gouraud", simple_texture));
	window_mode_value->add_component("camera", camera_system::get()->build_component(window_mode_value, camera_type::ORTHO));

	// Window mode transform
	transform_data window_transform;
	window_transform.x = 0;
	window_transform.y = 120;
	window_transform.scale.x = 100;
	window_transform.scale.y = 30;
	// Window mode
	auto window_mode = entity_manager::get()->create_entity("WindowMode", state_type::SETTINGS, window_transform);
	window_mode->add_component("render", renderer::get()->build_component(window_mode, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/window_mode.png", "rectangle", "Gouraud", simple_texture));
	window_mode->add_component("camera", camera_system::get()->build_component(window_mode, camera_type::ORTHO));


	// Title transform
	transform_data title_transform;
	title_transform.x = x_size / 2 - 200;
	title_transform.y = y_size - 250;
	// Title
	auto title = entity_manager::get()->create_entity("Title", state_type::SETTINGS, title_transform);
	title->add_component("render", renderer::get()->build_component(title, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	title->add_component("text", text_system::get()->build_component(title, "SETTINGS"));

	// Buttons

	int x_center = x_size / 2;
	int y_center = y_size / 2;

	int x_button_size = 25;
	int y_button_size = 25;

	// resolution right arrow trans
	transform_data resolution_right_arrow_transform;
	resolution_right_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	resolution_right_arrow_transform.x = 250;
	resolution_right_arrow_transform.y = 180;

	// resolution left arrow trans
	transform_data resolution_left_arrow_transform;
	resolution_left_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	resolution_left_arrow_transform.x = -250;
	resolution_left_arrow_transform.y = 180;

	// Right arrow button for resolution
	auto resolution_button_right = entity_manager::get()->create_entity("resolution_arrow_right", state_type::SETTINGS, resolution_right_arrow_transform);
	resolution_button_right->add_component("clickable", clickable_system::get()->build_component(resolution_button_right, glm::dvec2(resolution_right_arrow_transform.x, -resolution_right_arrow_transform.y), glm::dvec2(x_button_size, y_button_size)));
	resolution_button_right->add_component("render", renderer::get()->build_component(resolution_button_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/arrow_right.png", "rectangle", "Gouraud", simple_texture));
	resolution_button_right->add_component("camera", camera_system::get()->build_component(resolution_button_right, camera_type::ORTHO));

	// Left arrow button for resolution
	auto resolution_button_left = entity_manager::get()->create_entity("resolution_arrow_left", state_type::SETTINGS, resolution_left_arrow_transform);
	resolution_button_left->add_component("clickable", clickable_system::get()->build_component(resolution_button_left, glm::dvec2(resolution_left_arrow_transform.x, -resolution_left_arrow_transform.y), glm::dvec2(x_button_size, y_button_size)));
	resolution_button_left->add_component("render", renderer::get()->build_component(resolution_button_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/arrow_left.png", "rectangle", "Gouraud", simple_texture));
	resolution_button_left->add_component("camera", camera_system::get()->build_component(resolution_button_left, camera_type::ORTHO));

	// window mode right arrow trans
	transform_data window_mode_right_arrow_transform;
	window_mode_right_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	window_mode_right_arrow_transform.x = 250;
	window_mode_right_arrow_transform.y = 60;

	// resolution left arrow trans
	transform_data window_mode_left_arrow_transform;
	window_mode_left_arrow_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	window_mode_left_arrow_transform.x = -250;
	window_mode_left_arrow_transform.y = 60;

	// Right arrow button for window mode
	auto window_mode_button_right = entity_manager::get()->create_entity("window_mode_arrow_right", state_type::SETTINGS, window_mode_right_arrow_transform);
	window_mode_button_right->add_component("clickable", clickable_system::get()->build_component(window_mode_button_right, glm::dvec2(window_mode_right_arrow_transform.x, -window_mode_right_arrow_transform.y), glm::dvec2(x_button_size, y_button_size)));
	window_mode_button_right->add_component("render", renderer::get()->build_component(window_mode_button_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/arrow_right.png", "rectangle", "Gouraud", simple_texture));
	window_mode_button_right->add_component("camera", camera_system::get()->build_component(window_mode_button_right, camera_type::ORTHO));

	// Left arrow button for window mode
	auto window_mode_button_left = entity_manager::get()->create_entity("window_mode_arrow_left", state_type::SETTINGS, window_mode_left_arrow_transform);
	window_mode_button_left->add_component("clickable", clickable_system::get()->build_component(window_mode_button_left, glm::dvec2(window_mode_left_arrow_transform.x, -window_mode_left_arrow_transform.y), glm::dvec2(x_button_size, y_button_size)));
	window_mode_button_left->add_component("render", renderer::get()->build_component(window_mode_button_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/arrow_left.png", "rectangle", "Gouraud", simple_texture));
	window_mode_button_left->add_component("camera", camera_system::get()->build_component(window_mode_button_left, camera_type::ORTHO));

	// move left trans
	transform_data move_left_transform;
	move_left_transform.scale = glm::vec3(100, 30, 1.0f);
	move_left_transform.x = -30;
	move_left_transform.y = -60;

	// move left
	auto move_left = entity_manager::get()->create_entity("moveLeft", state_type::SETTINGS, move_left_transform);
	move_left->add_component("render", renderer::get()->build_component(move_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/move_left.png", "rectangle", "Gouraud", simple_texture));
	move_left->add_component("camera", camera_system::get()->build_component(move_left, camera_type::ORTHO));

	// move right trans
	transform_data move_right_transform;
	move_right_transform.scale = glm::vec3(100, 30, 1.0f);
	move_right_transform.x = -30;
	move_right_transform.y = -120;

	// move right
	auto move_right = entity_manager::get()->create_entity("moveRight", state_type::SETTINGS, move_right_transform);
	move_right->add_component("render", renderer::get()->build_component(move_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/move_right.png", "rectangle", "Gouraud", simple_texture));
	move_right->add_component("camera", camera_system::get()->build_component(move_right, camera_type::ORTHO));

	// key move left trans
	transform_data key_move_left_transform;
	key_move_left_transform.scale = glm::vec3(15, 15, 1.0f);
	key_move_left_transform.x = 90;
	key_move_left_transform.y = -60;

	std::string letter_left;
	letter_left = (char)input_handler::get()->glfw_button_left;
	std::string path_left = "res/textures/letters/" + letter_left + ".png";

	// key move left
	auto key_move_left = entity_manager::get()->create_entity("keyMoveLeft", state_type::SETTINGS, key_move_left_transform);
	key_move_left->add_component("clickable", clickable_system::get()->build_component(key_move_left, glm::dvec2(key_move_left_transform.x, -key_move_left_transform.y), glm::dvec2(15, 15)));
	key_move_left->add_component("render", renderer::get()->build_component(key_move_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), path_left, "rectangle", "Gouraud", simple_texture));
	key_move_left->add_component("camera", camera_system::get()->build_component(key_move_left, camera_type::ORTHO));

	// key move right trans
	transform_data key_move_right_transform;
	key_move_right_transform.scale = glm::vec3(15, 15, 1.0f);
	key_move_right_transform.x = 90;
	key_move_right_transform.y = -120;

	std::string letter_right;
	letter_right = (char)input_handler::get()->glfw_button_right;
	std::string path_right = "res/textures/letters/" + letter_right + ".png";

	// key move right
	auto key_move_right = entity_manager::get()->create_entity("keyMoveRight", state_type::SETTINGS, key_move_right_transform);
	key_move_right->add_component("clickable", clickable_system::get()->build_component(key_move_right, glm::dvec2(key_move_right_transform.x, -key_move_right_transform.y), glm::dvec2(15, 15)));
	key_move_right->add_component("render", renderer::get()->build_component(key_move_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), path_right, "rectangle", "Gouraud", simple_texture));
	key_move_right->add_component("camera", camera_system::get()->build_component(key_move_right, camera_type::ORTHO));

	// Controls trans
	transform_data controls_transform;
	controls_transform.scale = glm::vec3(100, 30, 1.0f);
	controls_transform.x = 0;
	controls_transform.y = 0;

	// Controls
	auto controls = entity_manager::get()->create_entity("controls", state_type::SETTINGS, controls_transform);
	controls->add_component("render", renderer::get()->build_component(controls, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/controls.png", "rectangle", "Gouraud", simple_texture));
	controls->add_component("camera", camera_system::get()->build_component(controls, camera_type::ORTHO));

	transform_data text_transform;
	text_transform.x = 10;
	text_transform.y = 10;
	auto help_text = entity_manager::get()->create_entity("help_text", state_type::SETTINGS, text_transform);
	help_text->add_component("render", renderer::get()->build_component(help_text, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	help_text->add_component("text", text_system::get()->build_component(help_text, " "));

	selection = resolution_button;
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

void determine_screen_res(resolution &res)
{
	switch (res)
	{
	case _1024x768:
		glfwSetWindowSize(glfw::window, 1024, 768);
		renderer::get()->change_texture(entity_manager::get()->get_entity("resolutionValue"), "res/textures/1024x768.png");
		break;
	case _1280x720:
		glfwSetWindowSize(glfw::window, 1280, 720);
		renderer::get()->change_texture(entity_manager::get()->get_entity("resolutionValue"), "res/textures/1280x720.png");
		break;
	case _1600x1200:
		glfwSetWindowSize(glfw::window, 1600, 1200);
		renderer::get()->change_texture(entity_manager::get()->get_entity("resolutionValue"), "res/textures/1600x1200.png");
		break;
	case _1920x1080:
		glfwSetWindowSize(glfw::window, 1920, 1080);
		renderer::get()->change_texture(entity_manager::get()->get_entity("resolutionValue"), "res/textures/1920x1080.png");
		break;
	}
}

void determine_window_mode(window_mode &window_mode)
{
	switch (window_mode)
	{
	case fullscreen:
		// Handle logic for fullscreen
		break;
	case windowed:
		// Handle logic for windowed
		break;
	}
}

void handle_remap_key_left()
{
	glfwSetKeyCallback(glfw::window, key_callback);
	// Update prompt
	std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("help_text")->get_component("text"));
	tc->_data->text = "Assign key, ESC to cancel...";
	// Force render before going into the while loop.
	renderer::get()->render();
	while (true)
	{
		// Check for events
		glfwPollEvents();
		if (latest_key_press != -1)
		{
			if (latest_key_press == GLFW_KEY_ESCAPE)
				break;
			std::string letter;
			letter = (char)latest_key_press;
			std::cout << "res/textures/letters/" + letter + ".png" << std::endl;
			// Update texture to new letter
			if (latest_key_press >= 65 && latest_key_press <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			std::ofstream user_pref_file;
			// Open file and clear
			user_pref_file.open("res/buttons.txt", std::ofstream::out | std::ofstream::trunc);
			if (user_pref_file.is_open())
			{
				// Add new button and old buttons
				user_pref_file << "Left: " << latest_key_press << "\n";
				user_pref_file << "Right: " << input_handler::get()->glfw_button_right << "\n";
				user_pref_file << "Front: " << input_handler::get()->glfw_button_up << "\n";
				user_pref_file << "Back: " << input_handler::get()->glfw_button_down << "\n";
			}
			// Close
			user_pref_file.close();
			// Re-load input keys
			input_handler::get()->load_input_settings();
			// Remove actuall callback
			glfwSetKeyCallback(glfw::window, key_callback_fake);
			break;
		}
	}
}

void handle_remap_key_right()
{
	glfwSetKeyCallback(glfw::window, key_callback);
	// Update prompt
	std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("help_text")->get_component("text"));
	tc->_data->text = "Assign key, ESC to cancel...";
	// Force render before going into the while loop.
	renderer::get()->render();
	while (true)
	{
		// Check for events
		glfwPollEvents();

		if (latest_key_press != -1)
		{
			if (latest_key_press == GLFW_KEY_ESCAPE)
				break;
			std::string letter;
			letter = (char)latest_key_press;
			std::cout << "res/textures/letters/" + letter + ".png" << std::endl;
			// Update texture to new letter
			if (latest_key_press >= 65 && latest_key_press <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			std::ofstream user_pref_file;
			// Open file and clear
			user_pref_file.open("res/buttons.txt", std::ofstream::out | std::ofstream::trunc);
			if (user_pref_file.is_open())
			{
				// Add new button and old buttons
				user_pref_file << "Left: " << input_handler::get()->glfw_button_left << "\n";
				user_pref_file << "Right: " << latest_key_press << "\n";
				user_pref_file << "Front: " << input_handler::get()->glfw_button_up << "\n";
				user_pref_file << "Back: " << input_handler::get()->glfw_button_down << "\n";
			}
			// Close
			user_pref_file.close();
			// Re-load input keys
			input_handler::get()->load_input_settings();
			// Remove actuall callback
			glfwSetKeyCallback(glfw::window, key_callback_fake);
			break;
		}

	}
}

void settings_state::on_update(float delta_time)
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
		std::string letter_right;
		std::string letter_left;
		letter_right = (char)input_handler::get()->glfw_button_right;
		letter_left = (char)input_handler::get()->glfw_button_left;
		switch (selection)
		{
		case back_button:
			selection = move_right_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark_selected.png");

			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case move_right_button:
			selection = move_left_button;
	
			// Update texture to new letter
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			break;
		case move_left_button:
			selection = window_mode_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left_selected.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case window_mode_button:
			selection = resolution_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left_selected.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case resolution_button:
			selection = back_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
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
		std::string letter_right;
		std::string letter_left;
		letter_right = (char)input_handler::get()->glfw_button_right;
		letter_left = (char)input_handler::get()->glfw_button_left;
		switch (selection)
		{
		case resolution_button:
			selection = window_mode_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left_selected.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case window_mode_button:
			selection = move_left_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			break;
		case move_left_button:
			selection = move_right_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case move_right_button:
			selection = back_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;
		case back_button:
			selection = resolution_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_left"), "res/textures/arrow_left_selected.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("resolution_arrow_right"), "res/textures/arrow_right_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_left"), "res/textures/arrow_left.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("window_mode_arrow_right"), "res/textures/arrow_right.png");
			renderer::get()->change_texture(entity_manager::get()->get_entity("back_button"), "res/textures/back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
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
		case back_button:
			engine_state_machine::get()->change_state("menu_state", true);
			break;
		case move_left_button:
			handle_remap_key_left();
			break;
		case move_right_button:
			handle_remap_key_right();
			break;
		}
	}


	// Right arrow
	static int right_old_state = GLFW_RELEASE;
	int right_state = glfwGetKey(glfw::window, GLFW_KEY_RIGHT);

	// Left arrow
	static int left_old_state = GLFW_RELEASE;
	int left_state = glfwGetKey(glfw::window, GLFW_KEY_LEFT);

	//std::cout << "********** SETTINGS DISPLAYED ****************" << std::endl;
	std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));
	if (cs->get_clicked_component_name() == "resolution_arrow_right" || (right_state == GLFW_RELEASE && right_old_state == GLFW_PRESS && selection == resolution_button))
	{
		// Wrap around
		switch (current_resolution)
		{
		case _1024x768:
			current_resolution = _1280x720;
			break;
		case _1280x720:
			current_resolution = _1600x1200;
			break;
		case _1600x1200:
			current_resolution = _1920x1080;
			break;
		case _1920x1080:
			current_resolution = _1024x768;
			break;
		}
		determine_screen_res(current_resolution);

		//glfwSetWindowSize(glfw::window, 1600, 1200);
		cs->clear_clicked_component_name();

	}
	else if (cs->get_clicked_component_name() == "resolution_arrow_left" || (left_state == GLFW_RELEASE && left_old_state == GLFW_PRESS && selection == resolution_button))
	{
		// Wrap around
		switch (current_resolution)
		{
		case _1024x768:
			current_resolution = _1920x1080;
			break;
		case _1280x720:
			current_resolution = _1024x768;
			break;
		case _1600x1200:
			current_resolution = _1280x720;
			break;
		case _1920x1080:
			current_resolution = _1600x1200;
			break;
		}
		determine_screen_res(current_resolution);

		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "window_mode_arrow_left" || (left_state == GLFW_RELEASE && left_old_state == GLFW_PRESS && selection == window_mode_button))
	{
		// Wrap around
		switch (current_window_mode)
		{
		case windowed:
			current_window_mode = fullscreen;
			break;
		case fullscreen:
			current_window_mode = windowed;
			break;
		}
		determine_window_mode(current_window_mode);
		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "window_mode_arrow_right" || (right_state == GLFW_RELEASE && right_old_state == GLFW_PRESS && selection == window_mode_button))
	{
		// Wrap around
		switch (current_window_mode)
		{
		case windowed:
			current_window_mode = fullscreen;
			break;
		case fullscreen:
			current_window_mode = windowed;
			break;
		}
		determine_window_mode(current_window_mode);
		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "keyMoveLeft")
	{
		handle_remap_key_left();
		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "keyMoveRight")
	{
		handle_remap_key_right();
		cs->clear_clicked_component_name();
	}
	// Reset key states
	left_old_state = left_state;
	right_old_state = right_state;

	up_old_state = up_state;
	down_old_state = down_state;
	enter_old_state = enter_state;
	// Reset controller button states
	if (present)
	{
		up_old_axis = axes[10];
		down_old_axis = axes[12];
		enter_joystick_old_state = axes[0];
	}

	
}

void settings_state::on_exit()
{
	std::cout << "Exiting settings state" << std::endl;
}