#define GLM_ENABLE_EXPERIMENTAL
#include "game_over_state.h"
#include "entity_manager.h"
#include <iostream>
#include <stdlib.h>
#include <mysql.h>

using namespace std;


void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	std::cout << (char)codepoint << std::endl;
	// add character
	name.push_back((char)codepoint);

	std::shared_ptr<text_component> score = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("your_score")->get_component("text"));
	std::string player_name = " ";

	// print name
	for (size_t i = 0; i < name.size(); i++)
	{
		std::cout << name[i];
		player_name += (char)name[i];
	}
	if (name.size() > 0)
		score->_data->text = player_name;
	else
		score->_data->text = " ";
	std::cout << std::endl;
}
// circular dependency issue, game_over_state somehow includes settings_state, named key_callback2 to avoid
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
	{
		std::shared_ptr<text_component> score = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("your_score")->get_component("text"));
		if (name.size() > 0)
		{
			std::string player_name = " ";
			// delete last character
			name.pop_back();
			// print name
			for (size_t i = 0; i < name.size(); i++)
			{
				std::cout << name[i];
				player_name += (char)name[i];
			}
			score->_data->text = player_name;
			std::cout << std::endl;
		}
		else
		{
			score->_data->text = " ";
		}
	}

}

void game_over_state::initialise()
{
	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size / 1.25, y_size / 1.25, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::GAME_OVER, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// Game over text transform
	transform_data game_over_transform;
	game_over_transform.x = x_size / 2 - 230;
	game_over_transform.y = y_size - 250;
	// Game over
	auto game_over_text = entity_manager::get()->create_entity("game_over", state_type::GAME_OVER, game_over_transform);
	game_over_text->add_component("render", renderer::get()->build_component(game_over_text, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	game_over_text->add_component("text", text_system::get()->build_component(game_over_text, "GAME OVER"));


	int x_button_size = 100;
	int y_button_size = 50;

	// Buttons transformations
	// Menu button
	transform_data menu_button_transform;
	menu_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	menu_button_transform.y = 125.0f;

	auto button_menu = entity_manager::get()->create_entity("menu_button2", state_type::GAME_OVER, menu_button_transform);
	button_menu->add_component("render", renderer::get()->build_component(button_menu, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/menu_button2_selected.png", "rectangle", "Gouraud", simple_texture));
	button_menu->add_component("clickable", clickable_system::get()->build_component(button_menu, glm::dvec2(0, -125), glm::dvec2(x_button_size, y_button_size)));
	button_menu->add_component("camera", camera_system::get()->build_component(button_menu, camera_type::ORTHO));

	transform_data submit_score_button_transform;
	submit_score_button_transform.scale = glm::vec3(x_button_size, y_button_size, 1.0f);
	submit_score_button_transform.y = 0.0f;

	auto submit_score_button = entity_manager::get()->create_entity("submit_score_button", state_type::GAME_OVER, submit_score_button_transform);
	submit_score_button->add_component("render", renderer::get()->build_component(submit_score_button, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/submit_score_button.png", "rectangle", "Gouraud", simple_texture));
	submit_score_button->add_component("clickable", clickable_system::get()->build_component(submit_score_button, glm::dvec2(0, 0), glm::dvec2(x_button_size, y_button_size)));
	submit_score_button->add_component("camera", camera_system::get()->build_component(submit_score_button, camera_type::ORTHO));

}

void game_over_state::display_high_scores()
{
	entity_manager::get()->delete_entity("menu_button2");
	entity_manager::get()->delete_entity("submit_score_button");
	entity_manager::get()->delete_entity("game_over");

	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	// High scores text transform
	transform_data menu_transform;
	menu_transform.x = x_size / 2 - 230;
	menu_transform.y = y_size - 250;
	// High scores
	auto menu_text = entity_manager::get()->create_entity("highScores", state_type::GAME_OVER, menu_transform);
	menu_text->add_component("render", renderer::get()->build_component(menu_text, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	menu_text->add_component("text", text_system::get()->build_component(menu_text, "HIGH SCORES"));

	printf("MySQL client version: %s\n", mysql_get_client_info());

	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
	}

	if (mysql_real_connect(con, "db63.grserver.gr", "manos_rtm", "o0gN9$u8",
		"manos_race_the_moon", 3306, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}

	if (mysql_query(con, "SELECT * FROM high_scores ORDER BY score DESC LIMIT 8"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	}

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
			high_scores.push_back(row[i]);
		}
		printf("\n");
	}

	//if (mysql_query(con, "INSERT INTO high_scores VALUES('test',999)")) {
	//	fprintf(stderr, "%s\n", mysql_error(con));
	//	mysql_close(con);
	//}

	mysql_free_result(result);
	mysql_close(con);

	for (size_t i = 0; i < high_scores.size(); i++)
	{
		std::cout << "high score count: " << high_scores.size() << std::endl;
		transform_data text_transform;
		text_transform.x = x_size / 2 - 150;
		if (i % 2 == 0)
			text_transform.y = y_size - 300 - i * 25;
		else
			text_transform.y = y_size - 300 - i * 25 + 5;
		auto test = entity_manager::get()->create_entity("score" + std::to_string(i), state_type::GAME_OVER, text_transform);
		test->add_component("render", renderer::get()->build_component(test, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
		test->add_component("text", text_system::get()->build_component(test, high_scores[i]));
	}
	glfwSetCharCallback(glfw::window, character_callback);
	glfwSetKeyCallback(glfw::window, key_callback2);

	//transform_data your_score_prompt_transform;
	//your_score_prompt_transform.x = x_size / 2 - 150;
	//your_score_prompt_transform.y = 10;
	//auto your_score_prompt = entity_manager::get()->create_entity("your_score_prompt", state_type::GAME_OVER, your_score_prompt_transform);
	//your_score_prompt->add_component("render", renderer::get()->build_component(your_score_prompt, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	//your_score_prompt->add_component("text", text_system::get()->build_component(your_score_prompt, "Your score:"));

	transform_data your_name_prompt_transform;
	your_name_prompt_transform.x = x_size / 2 - 400;
	your_name_prompt_transform.y = 10;
	auto your_name_prompt = entity_manager::get()->create_entity("your_score_prompt", state_type::GAME_OVER, your_name_prompt_transform);
	your_name_prompt->add_component("render", renderer::get()->build_component(your_name_prompt, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	your_name_prompt->add_component("text", text_system::get()->build_component(your_name_prompt, "Your name:"));

	transform_data text_transform;
	text_transform.x = x_size / 2 - 150;
	text_transform.y = 10;
	auto test = entity_manager::get()->create_entity("your_score", state_type::GAME_OVER, text_transform);
	test->add_component("render", renderer::get()->build_component(test, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	test->add_component("text", text_system::get()->build_component(test, " "));

	transform_data help_text_transform;
	help_text_transform.x = x_size / 2 - 500;
	help_text_transform.y = 60;
	help_text_transform.z = 16;
	auto help_text = entity_manager::get()->create_entity("help_text_game_over", state_type::GAME_OVER, help_text_transform);
	help_text->add_component("render", renderer::get()->build_component(help_text, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	help_text->add_component("text", text_system::get()->build_component(help_text, "Type your name and press enter to submit..."));
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
	std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));
	if (cs->get_clicked_component_name() == "submit_score_button")
	{
		display_high_scores();
		cs->clear_clicked_component_name();
	}
}

void game_over_state::on_exit()
{
	std::cout << "Exiting game over state" << std::endl;
}