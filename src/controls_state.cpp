#define GLM_ENABLE_EXPERIMENTAL
#include "controls_state.h"
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
			input_handler::get()->glfw_button_left = latest_key_press;
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

			input_handler::get()->glfw_button_right = latest_key_press;
			// Remove actuall callback
			glfwSetKeyCallback(glfw::window, key_callback_fake);
			break;
		}

	}
}

void handle_remap_joystick_enter()
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (present)
	{
		//glfwSetKeyCallback(glfw::window, key_callback);


		// Update prompt
		std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("help_text")->get_component("text"));
		tc->_data->text = "Assign key, ESC to cancel...";
		// Force render before going into the while loop.
		renderer::get()->render();
		while (true)
		{
			int count;
			const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
			static int button = -1;
			static char old_state = GLFW_RELEASE;
			for (size_t i = 0; i < count; i++)
			{
				if (axes[i] == GLFW_PRESS)
				{
					button = i;
					std::cout << " ====== " << i << std::endl;
				}
			}
			// Check for events
			glfwPollEvents();

			if (button != -1 && axes[button] == GLFW_RELEASE && old_state == GLFW_PRESS)
			{
				if (button == 0)
					renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
				else if (button == 1)
					renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
				else if (button == 2)
					renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
				else if (button == 3)
					renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
				else
					renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");
				std::cout << "Before setting: " << input_handler::get()->glfw_joystick_enter << std::endl;
				input_handler::get()->glfw_joystick_enter = button;
				std::cout << "After setting: " << input_handler::get()->glfw_joystick_enter << std::endl;
				// Remove actuall callback
				//glfwSetKeyCallback(glfw::window, key_callback_fake);
				std::shared_ptr<text_component> tc = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("help_text")->get_component("text"));
				tc->_data->text = " ";
				button = -1;
				break;
			}
			old_state = axes[button];
		}
	}
}

void controls_state::initialise()
{
	glfwSetKeyCallback(glfw::window, key_callback_fake);
	latest_key_press = -1;
	initText2D("res/textures/myriad.png");

	int x_size = 0;
	int y_size = 0;

	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(1920 * 0.5, 1080 * 0.5, 1.0f);
	back_transform.z = -500;
	auto background = entity_manager::get()->create_entity("background", state_type::CONTROLS, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Title transform
	transform_data title_transform;
	title_transform.x = x_size / 2 - 100;
	title_transform.y = y_size - 50;
	// Title
	auto title = entity_manager::get()->create_entity("title_controls", state_type::CONTROLS, title_transform);
	title->add_component("render", renderer::get()->build_component(title, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	title->add_component("text", text_system::get()->build_component(title, "CONTROLS"));

	// move left trans
	transform_data move_left_transform;
	move_left_transform.scale = glm::vec3(100, 30, 1.0f);
	move_left_transform.x = -30 - 400;
	move_left_transform.y = -60;

	// move left
	auto move_left = entity_manager::get()->create_entity("moveLeft", state_type::CONTROLS, move_left_transform);
	move_left->add_component("render", renderer::get()->build_component(move_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/move_left.png", "rectangle", "Gouraud", simple_texture));
	move_left->add_component("camera", camera_system::get()->build_component(move_left, camera_type::ORTHO));

	// move right trans
	transform_data move_right_transform;
	move_right_transform.scale = glm::vec3(100, 30, 1.0f);
	move_right_transform.x = -30 - 400;
	move_right_transform.y = -120;

	// move right
	auto move_right = entity_manager::get()->create_entity("moveRight", state_type::CONTROLS, move_right_transform);
	move_right->add_component("render", renderer::get()->build_component(move_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/move_right.png", "rectangle", "Gouraud", simple_texture));
	move_right->add_component("camera", camera_system::get()->build_component(move_right, camera_type::ORTHO));

	//// menu enter transform
	//transform_data menu_enter_transform;
	//menu_enter_transform.scale = glm::vec3(100, 30, 1.0f);
	//menu_enter_transform.x = -30 - 400;
	//menu_enter_transform.y = -180;

	//// menu enter
	//auto menu_enter = entity_manager::get()->create_entity("menuEnter", state_type::CONTROLS, menu_enter_transform);
	//menu_enter->add_component("render", renderer::get()->build_component(menu_enter, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/menu_accept.png", "rectangle", "Gouraud", simple_texture));
	//menu_enter->add_component("camera", camera_system::get()->build_component(menu_enter, camera_type::ORTHO));

	// menu enter transform
	transform_data menu_enter_joystick_transform;
	menu_enter_joystick_transform.scale = glm::vec3(100, 30, 1.0f);
	menu_enter_joystick_transform.x = -30 + 400;
	menu_enter_joystick_transform.y = -60;

	// menu enter
	auto menu_enter_joystick = entity_manager::get()->create_entity("menuEnterJoystick", state_type::CONTROLS, menu_enter_joystick_transform);
	menu_enter_joystick->add_component("render", renderer::get()->build_component(menu_enter_joystick, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/menu_accept.png", "rectangle", "Gouraud", simple_texture));
	menu_enter_joystick->add_component("camera", camera_system::get()->build_component(menu_enter_joystick, camera_type::ORTHO));

	// Back button transform
	transform_data back_button_transform;
	back_button_transform.x = 0;
	back_button_transform.y = -270;
	back_button_transform.scale.x = 100;
	back_button_transform.scale.y = 50;
	// Back button
	auto back_button = entity_manager::get()->create_entity("controls_back_button", state_type::CONTROLS, back_button_transform);
	back_button->add_component("render", renderer::get()->build_component(back_button, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/back_button.png", "rectangle", "Gouraud", simple_texture));
	back_button->add_component("camera", camera_system::get()->build_component(back_button, camera_type::ORTHO));
	back_button->add_component("clickable", clickable_system::get()->build_component(back_button, vec2(back_button_transform.x, -back_button_transform.y), back_button_transform.scale));

	// key move left trans
	transform_data key_move_left_transform;
	key_move_left_transform.scale = glm::vec3(15, 15, 1.0f);
	key_move_left_transform.x = 90 - 400;
	key_move_left_transform.y = -60;

	std::string letter_left;
	letter_left = (char)input_handler::get()->glfw_button_left;
	std::string path_left = "res/textures/letters/" + letter_left + ".png";

	// key move left
	auto key_move_left = entity_manager::get()->create_entity("keyMoveLeft", state_type::CONTROLS, key_move_left_transform);
	key_move_left->add_component("clickable", clickable_system::get()->build_component(key_move_left, glm::dvec2(key_move_left_transform.x, -key_move_left_transform.y), glm::dvec2(15, 15)));
	key_move_left->add_component("render", renderer::get()->build_component(key_move_left, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), path_left, "rectangle", "Gouraud", simple_texture));
	key_move_left->add_component("camera", camera_system::get()->build_component(key_move_left, camera_type::ORTHO));

	// key move right trans
	transform_data key_move_right_transform;
	key_move_right_transform.scale = glm::vec3(15, 15, 1.0f);
	key_move_right_transform.x = 90 - 400;
	key_move_right_transform.y = -120;

	std::string letter_right;
	letter_right = (char)input_handler::get()->glfw_button_right;
	std::string path_right = "res/textures/letters/" + letter_right + ".png";

	// key move right
	auto key_move_right = entity_manager::get()->create_entity("keyMoveRight", state_type::CONTROLS, key_move_right_transform);
	key_move_right->add_component("clickable", clickable_system::get()->build_component(key_move_right, glm::dvec2(key_move_right_transform.x, -key_move_right_transform.y), glm::dvec2(15, 15)));
	key_move_right->add_component("render", renderer::get()->build_component(key_move_right, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), path_right, "rectangle", "Gouraud", simple_texture));
	key_move_right->add_component("camera", camera_system::get()->build_component(key_move_right, camera_type::ORTHO));

	// key menu move left trans
	transform_data key_menu_enter_joystick_transform;
	key_menu_enter_joystick_transform.scale = glm::vec3(15, 15, 1.0f);
	key_menu_enter_joystick_transform.x = 90 + 400;
	key_menu_enter_joystick_transform.y = -60;

	// key menu move left
	auto key_menu_enter_joystick = entity_manager::get()->create_entity("keyMenuEnterJoystick", state_type::CONTROLS, key_menu_enter_joystick_transform);
	key_menu_enter_joystick->add_component("clickable", clickable_system::get()->build_component(key_menu_enter_joystick, glm::dvec2(key_menu_enter_joystick_transform.x, -key_menu_enter_joystick_transform.y), glm::dvec2(15, 15)));
	key_menu_enter_joystick->add_component("render", renderer::get()->build_component(key_menu_enter_joystick, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/letters/question_mark.png", "rectangle", "Gouraud", simple_texture));
	key_menu_enter_joystick->add_component("camera", camera_system::get()->build_component(key_menu_enter_joystick, camera_type::ORTHO));

	if (input_handler::get()->glfw_joystick_enter == 0)
		renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
	else if (input_handler::get()->glfw_joystick_enter == 1)
		renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
	else if (input_handler::get()->glfw_joystick_enter == 2)
		renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
	else if (input_handler::get()->glfw_joystick_enter == 3)
		renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");

	//// key menu move left trans
	//transform_data key_menu_enter_transform;
	//key_menu_enter_transform.scale = glm::vec3(15, 15, 1.0f);
	//key_menu_enter_transform.x = 90 - 400;
	//key_menu_enter_transform.y = -180;

	//// key menu move left
	//auto key_menu_enter = entity_manager::get()->create_entity("keyMenuEnter", state_type::CONTROLS, key_menu_enter_transform);
	//key_menu_enter->add_component("clickable", clickable_system::get()->build_component(key_menu_enter, glm::dvec2(key_menu_enter_transform.x, -key_menu_enter_transform.y), glm::dvec2(15, 15)));
	//key_menu_enter->add_component("render", renderer::get()->build_component(key_menu_enter, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/letters/question_mark.png", "rectangle", "Gouraud", simple_texture));
	//key_menu_enter->add_component("camera", camera_system::get()->build_component(key_menu_enter, camera_type::ORTHO));

	// Keyboard trans
	transform_data keyboard_transform;
	keyboard_transform.scale = glm::vec3(100, 30, 1.0f);
	keyboard_transform.x = -400;
	keyboard_transform.y = 0;

	// Keyboard
	auto keyboard = entity_manager::get()->create_entity("keyboard", state_type::CONTROLS, keyboard_transform);
	keyboard->add_component("render", renderer::get()->build_component(keyboard, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/keyboard.png", "rectangle", "Gouraud", simple_texture));
	keyboard->add_component("camera", camera_system::get()->build_component(keyboard, camera_type::ORTHO));

	// Joystick trans
	transform_data joystick_transform;
	joystick_transform.scale = glm::vec3(100, 30, 1.0f);
	joystick_transform.x = 400;
	joystick_transform.y = 0;

	// Joystick
	auto joystick = entity_manager::get()->create_entity("controller", state_type::CONTROLS, joystick_transform);
	joystick->add_component("render", renderer::get()->build_component(joystick, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/controller.png", "rectangle", "Gouraud", simple_texture));
	joystick->add_component("camera", camera_system::get()->build_component(joystick, camera_type::ORTHO));

	transform_data text_transform;
	text_transform.x = 10;
	text_transform.y = 10;
	auto help_text = entity_manager::get()->create_entity("help_text", state_type::CONTROLS, text_transform);
	help_text->add_component("render", renderer::get()->build_component(help_text, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	help_text->add_component("text", text_system::get()->build_component(help_text, " "));

}

void controls_state::on_reset()
{

}

void controls_state::on_enter()
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

	std::cout << "Entered controls state, press ENTER to go to game state" << std::endl;
}

void controls_state::on_update(float delta_time)
{
	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);
	entity_manager::get()->get_entity("title_controls")->get_trans().x = x_size / 2 - 100;
	entity_manager::get()->get_entity("title_controls")->get_trans().y = y_size - 50;

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	int count;
	const unsigned char* axes = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

	//std::cout << axes[10] << std::endl;
	static char up_old_axis = GLFW_RELEASE;
	//std::cout << count << std::endl;
	// Handle input for up arrow
	static int up_old_state = GLFW_RELEASE;
	int up_state = glfwGetKey(glfw::window, input_handler::get()->glfw_button_navigation_up);

	if ((up_state == GLFW_RELEASE && up_old_state == GLFW_PRESS) || (present && axes[input_handler::get()->glfw_joystick_up] == GLFW_RELEASE && up_old_axis == GLFW_PRESS))
	{
		std::string letter_right;
		std::string letter_left;
		letter_right = (char)input_handler::get()->glfw_button_right;
		letter_left = (char)input_handler::get()->glfw_button_left;
		switch (selection)
		{
		case controls_back_button:
			selection = enter_joystick_button;

			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y_selected.png");
			else 
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark_selected.png");

			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			break;
		case enter_joystick_button:
			selection = move_right_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");

			break;
		case move_right_button:
			selection = move_left_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");
			break;
		case move_left_button:
			selection = controls_back_button;
			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button_selected.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");

			break;
		}
		std::cout << selection << std::endl;
	}


	static char down_old_axis = GLFW_RELEASE;
	// Handle input for down arrow
	static int down_old_state = GLFW_RELEASE;
	int down_state = glfwGetKey(glfw::window, input_handler::get()->glfw_button_navigation_down);

	if ((down_state == GLFW_RELEASE && down_old_state == GLFW_PRESS) || (present && axes[input_handler::get()->glfw_joystick_down] == GLFW_RELEASE && down_old_axis == GLFW_PRESS))
	{
		std::string letter_right;
		std::string letter_left;
		letter_right = (char)input_handler::get()->glfw_button_right;
		letter_left = (char)input_handler::get()->glfw_button_left;
		switch (selection)
		{
		case move_left_button:
			selection = move_right_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
	
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");
			break;

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");

		case move_right_button:
			selection = enter_joystick_button;

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X_selected.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark_selected.png");
			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");

			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			
			break;
		case enter_joystick_button:
			selection = controls_back_button;

			// Set selected textures
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button_selected.png");

			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");

			break;
		case controls_back_button:
			selection = move_left_button;
			// Update texture to new letter
			if (input_handler::get()->glfw_button_left >= 65 && input_handler::get()->glfw_button_left <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/" + letter_left + "_selected.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveLeft"), "res/textures/letters/question_mark_selected.png");

			// Set normal textures for other states
			renderer::get()->change_texture(entity_manager::get()->get_entity("controls_back_button"), "res/textures/controls_back_button.png");
			if (input_handler::get()->glfw_button_right >= 65 && input_handler::get()->glfw_button_right <= 90)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/" + letter_right + ".png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMoveRight"), "res/textures/letters/question_mark.png");

			if (input_handler::get()->glfw_joystick_enter == 0)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/A.png");
			else if (input_handler::get()->glfw_joystick_enter == 1)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/B.png");
			else if (input_handler::get()->glfw_joystick_enter == 2)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/X.png");
			else if (input_handler::get()->glfw_joystick_enter == 3)
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/Y.png");
			else
				renderer::get()->change_texture(entity_manager::get()->get_entity("keyMenuEnterJoystick"), "res/textures/letters/question_mark.png");
			break;
		}
		std::cout << selection << std::endl;
	}

	static char enter_joystick_old_state = GLFW_RELEASE;
	static int enter_old_state = GLFW_RELEASE;
	int enter_state = glfwGetKey(glfw::window, GLFW_KEY_ENTER);
	if (enter_state == GLFW_RELEASE && enter_old_state == GLFW_PRESS || (present && axes[input_handler::get()->glfw_joystick_enter] == GLFW_RELEASE && enter_joystick_old_state == GLFW_PRESS))
	{
		switch (selection)
		{
		case controls_back_button:
			engine_state_machine::get()->change_state("settings_state", true);
			break;
		case move_left_button:
			handle_remap_key_left();
			break;
		case move_right_button:
			handle_remap_key_right();
			break;
		case enter_joystick_button:
			handle_remap_joystick_enter();
			break;
		}
	}

	up_old_state = up_state;
	down_old_state = down_state;
	enter_old_state = enter_state;

	if (present)
	{
		up_old_axis = axes[input_handler::get()->glfw_joystick_up];
		down_old_axis = axes[input_handler::get()->glfw_joystick_down];
		enter_joystick_old_state = axes[input_handler::get()->glfw_joystick_enter];
	}

	std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));

	if (cs->get_clicked_component_name() == "keyMoveLeft")
	{
		handle_remap_key_left();
		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "keyMoveRight")
	{
		handle_remap_key_right();
		cs->clear_clicked_component_name();
	}
	else if (cs->get_clicked_component_name() == "keyMenuEnterJoystick")
	{
		handle_remap_joystick_enter();
		//handle_remap_key_enter();
		cs->clear_clicked_component_name();
	}

}

void controls_state::on_exit()
{
	std::cout << "Exiting controls state" << std::endl;
}