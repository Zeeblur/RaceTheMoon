#define GLM_ENABLE_EXPERIMENTAL
#include "game_over_state.h"
#include "entity_manager.h"
#include <iostream>
#include <stdlib.h>
#include <mysql.h>
#include "engine_state_machine.h"
using namespace std;

void show_error(MYSQL *mysql)
{
	printf("Error(%d) [%s] \"%s\"", mysql_errno(mysql),
		mysql_sqlstate(mysql),
		mysql_error(mysql));
	mysql_close(mysql);
	my_sql_error = true;
	//exit(-1);
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	// Don't let user type ' and ", to avoid SQL injections
	if (!my_sql_error && codepoint != 34 && codepoint != 39)
	{
		std::cout << (char)codepoint << std::endl;
		// add character
		name.push_back((char)codepoint);

		std::shared_ptr<text_component> your_name = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("your_name")->get_component("text"));
		std::string player_name = " ";

		// print name
		for (size_t i = 0; i < name.size(); i++)
		{
			std::cout << name[i];
			player_name += (char)name[i];
		}
		if (name.size() > 0)
			your_name->_data->text = player_name;
		else
			your_name->_data->text = " ";
		std::cout << std::endl;
	}
}

void dummy_character_callback(GLFWwindow* window, unsigned int codepoint)
{
	// do nothing
}

void dummy_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// do nothing
}

void submit_score()
{
	if (!my_sql_error)
	{
		printf("MySQL client version: %s\n", mysql_get_client_info());

		MYSQL *con = mysql_init(NULL);

		if (con == NULL)
		{
			show_error(con);
		}
		// Establish connection
		if (mysql_real_connect(con, "db63.grserver.gr", "manos_rtm", "o0gN9$u8",
			"manos_race_the_moon", 3306, NULL, 0) == NULL)
		{
			show_error(con);
		}
		std::string player_name = "";

		// print name
		for (size_t i = 0; i < name.size(); i++)
		{
			std::cout << name[i];
			player_name += name[i];
		}
		// Prone to SQL injection
		std::string statement = "INSERT INTO high_scores VALUES(";
		statement += "'";
		statement += player_name;
		statement += "',";
		statement += std::to_string(current_score);
		statement += ")";
		std::cout << statement << std::endl;
		// Insert value
		if (mysql_query(con, statement.c_str())) {
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
		}
		// Close connection
		mysql_close(con);
	}
	engine_state_machine::get()->change_state("menu_state");
}

// circular dependency issue, game_over_state somehow includes settings_state, named key_callback2 to avoid
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE)
	{
		std::shared_ptr<text_component> your_name = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("your_name")->get_component("text"));
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
			your_name->_data->text = player_name;
			std::cout << std::endl;
		}
		else
		{
			your_name->_data->text = " ";
		}
	}
	//else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	//{
	//	action = GLFW_RELEASE;
	//	submit_score();
	//}

}

void game_over_state::initialise()
{
	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	transform_data back_transform;
	back_transform.scale = glm::vec3(x_size * 0.5, y_size * 0.5, 1.0f);
	back_transform.z = -1;
	auto background = entity_manager::get()->create_entity("background", state_type::GAME_OVER, back_transform);

	background->add_component("render", renderer::get()->build_component(background, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/race_the_moon.png", "rectangle", "Gouraud", simple_texture));
	background->add_component("camera", camera_system::get()->build_component(background, camera_type::ORTHO));

	// High scores text transform
	transform_data menu_transform;
	menu_transform.x = x_size / 2 - 100;
	menu_transform.y = y_size - 50;
	// High scores
	auto menu_text = entity_manager::get()->create_entity("highScores", state_type::GAME_OVER, menu_transform);
	menu_text->add_component("render", renderer::get()->build_component(menu_text, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), "res/textures/play_button.png", "rectangle", "text", text));
	menu_text->add_component("text", text_system::get()->build_component(menu_text, "HIGH SCORES"));

	transform_data your_score_prompt_transform;
	your_score_prompt_transform.x = x_size / 2 - 300;
	your_score_prompt_transform.y = 40;
	auto your_score_prompt = entity_manager::get()->create_entity("your_score_prompt", state_type::GAME_OVER, your_score_prompt_transform);
	your_score_prompt->add_component("render", renderer::get()->build_component(your_score_prompt, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	your_score_prompt->add_component("text", text_system::get()->build_component(your_score_prompt, "Your score: " + std::to_string(current_score)));

	transform_data your_name_prompt_transform;
	your_name_prompt_transform.x = x_size / 2 - 300;
	your_name_prompt_transform.y = 10;
	auto your_name_prompt = entity_manager::get()->create_entity("your_name_prompt", state_type::GAME_OVER, your_name_prompt_transform);
	your_name_prompt->add_component("render", renderer::get()->build_component(your_name_prompt, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	your_name_prompt->add_component("text", text_system::get()->build_component(your_name_prompt, "Your name:"));

	transform_data text_transform;
	text_transform.x = x_size / 2 - 50;
	text_transform.y = 10;
	auto test = entity_manager::get()->create_entity("your_name", state_type::GAME_OVER, text_transform);
	test->add_component("render", renderer::get()->build_component(test, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	test->add_component("text", text_system::get()->build_component(test, " "));

	transform_data help_text_transform;
	help_text_transform.x = x_size / 2 - 400;
	help_text_transform.y = 60;
	help_text_transform.z = 16;
	auto help_text = entity_manager::get()->create_entity("help_text_game_over", state_type::GAME_OVER, help_text_transform);
	help_text->add_component("render", renderer::get()->build_component(help_text, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
	help_text->add_component("text", text_system::get()->build_component(help_text, "Type your name and press enter to submit..."));

	printf("MySQL client version: %s\n", mysql_get_client_info());

	MYSQL *con = mysql_init(NULL);


	if (con == NULL)
	{
		show_error(con);
	}
	if (!my_sql_error)
	{
		if (mysql_real_connect(con, "db63.grserver.gr", "manos_rtm", "o0gN9$u8",
			"manos_race_the_moon", 3306, NULL, 0) == NULL)
		{
			show_error(con);
		}
		if (!my_sql_error)
		{
			if (mysql_query(con, "SELECT * FROM high_scores ORDER BY score DESC LIMIT 8"))
			{
				show_error(con);
			}
		}
		MYSQL_RES *result;
		if (!my_sql_error)
		{
			result = mysql_store_result(con);
		}
		if (!my_sql_error)
		{
			if (result == NULL)
			{
				show_error(con);
			}
		}
		int num_fields;
		if (!my_sql_error)
		{
			num_fields = mysql_num_fields(result);
		}
		MYSQL_ROW row;
		if (!my_sql_error)
		{
			while ((row = mysql_fetch_row(result)))
			{
				for (int i = 0; i < num_fields; i++)
				{
					printf("%s ", row[i] ? row[i] : "NULL");
					high_scores.push_back(row[i]);
				}
				printf("\n");
			}
		}
		if (!my_sql_error)
		{
			mysql_free_result(result);
			mysql_close(con);
		}
		
		if (!my_sql_error)
		{
			for (size_t i = 0; i < high_scores.size(); i++)
			{
				std::cout << "high score count: " << high_scores.size() << std::endl;
				transform_data text_transform;
				text_transform.x = x_size / 2 - 100;
				if (i % 2 == 0)
					text_transform.y = y_size - 100 - i * 25;
				else
					text_transform.y = y_size - 100 - i * 25 + 5;
				auto test = entity_manager::get()->create_entity("score" + std::to_string(i), state_type::GAME_OVER, text_transform);
				test->add_component("render", renderer::get()->build_component(test, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
				test->add_component("text", text_system::get()->build_component(test, high_scores[i]));
			}
		}
		else
		{
			transform_data no_connection_transform;
			no_connection_transform.x = x_size / 2 - 350;
			no_connection_transform.y = y_size / 2;
			no_connection_transform.z = 16;
			auto no_connection = entity_manager::get()->create_entity("no_connection", state_type::GAME_OVER, no_connection_transform);
			no_connection->add_component("render", renderer::get()->build_component(no_connection, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "res/textures/exit_button.png", "rectangle", "text", text));
			no_connection->add_component("text", text_system::get()->build_component(no_connection, "Could not connect to high score database."));
		}
	}

}

void game_over_state::display_high_scores()
{
	// Update score
	std::shared_ptr<text_component> your_score = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("your_score_prompt")->get_component("text"));
	your_score->_data->text = "Your score: " + std::to_string(current_score);

	if (!my_sql_error)
	{

		MYSQL *con = mysql_init(NULL);

		if (con == NULL)
		{
			show_error(con);
		}
		if (!my_sql_error)
		{

			if (mysql_real_connect(con, "db63.grserver.gr", "manos_rtm", "o0gN9$u8",
				"manos_race_the_moon", 3306, NULL, 0) == NULL)
			{
				show_error(con);
			}
			if (!my_sql_error)
			{
				if (mysql_query(con, "SELECT * FROM high_scores ORDER BY score DESC LIMIT 8"))
				{
					show_error(con);
				}
			}
			MYSQL_RES *result = mysql_store_result(con);
			if (!my_sql_error)
			{
				if (result == NULL)
				{
					show_error(con);
				}
			}
			int num_fields = mysql_num_fields(result);

			MYSQL_ROW row;
			if (!my_sql_error)
			{
				while ((row = mysql_fetch_row(result)))
				{
					for (int i = 0; i < num_fields; i++)
					{
						printf("%s ", row[i] ? row[i] : "NULL");
						high_scores.push_back(row[i]);
					}
					printf("\n");
				}
			}
			if (!my_sql_error)
			{
				mysql_free_result(result);
				mysql_close(con);
			}
			
			if (!my_sql_error)
			{
				for (size_t i = 0; i < high_scores.size(); i++)
				{
					if (entity_manager::get()->get_entity("score" + std::to_string(i)))
					{
						std::shared_ptr<text_component> score = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("score" + std::to_string(i))->get_component("text"));
						score->_data->text = high_scores[i] + " ";
					}
				}
			}
		}
	}


}

void game_over_state::on_reset()
{
	current_score = 0;
	name.clear();
}

void game_over_state::on_enter()
{
	auto m = engine::get()->get_subsystem("entity_manager");
	high_scores.clear();
	engine::get()->get_subsystem("entity_manager")->set_active(true);
	engine::get()->get_subsystem("entity_manager")->set_visible(true);
	engine::get()->get_subsystem("physics_system")->set_active(false);
	engine::get()->get_subsystem("clickable_system")->set_active(true);
	engine::get()->get_subsystem("renderer")->set_visible(true);

	glfwSetInputMode(glfw::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	current_score = score_system::get()->_data[0]->score;
	score_system::get()->_data[0]->score = 0;

	glfwSetCharCallback(glfw::window, character_callback);
	glfwSetKeyCallback(glfw::window, key_callback2);

	display_high_scores();

	std::cout << "Entered game over state, press ANY BUTTON to go to game state" << std::endl;
}


void game_over_state::on_update(float delta_time)
{
	int x_size = 0, y_size = 0;
	glfwGetWindowSize(glfw::window, &x_size, &y_size);

	entity_manager::get()->get_entity("your_score_prompt")->get_trans().x = x_size / 2 - 300;
	entity_manager::get()->get_entity("your_name_prompt")->get_trans().x = x_size / 2 - 300;
	entity_manager::get()->get_entity("help_text_game_over")->get_trans().x = x_size / 2 - 400;
	entity_manager::get()->get_entity("highScores")->get_trans().x = x_size / 2 - 100;
	entity_manager::get()->get_entity("highScores")->get_trans().y = y_size - 50;
	entity_manager::get()->get_entity("your_name")->get_trans().x = x_size / 2 - 50;

	if (!my_sql_error)
	{
		int count = 1;
		for (size_t i = 0; i < high_scores.size(); i++)
		{
			if (entity_manager::get()->get_entity("score" + std::to_string(i)))
			{
				entity_manager::get()->get_entity("score" + std::to_string(i))->get_trans().x = x_size / 2 - 100;

				if (i % 2 == 0)
					entity_manager::get()->get_entity("score" + std::to_string(i))->get_trans().y = y_size - 100 - i * 25;
				else
					entity_manager::get()->get_entity("score" + std::to_string(i))->get_trans().y = y_size - 100 - i * 25 + 5;

				std::shared_ptr<text_component> score = std::dynamic_pointer_cast<text_component>(entity_manager::get()->get_entity("score" + std::to_string(i))->get_component("text"));
				if (i % 2 == 0)
				{
					score->_data->text = std::to_string(count) + " -" + high_scores[i];
					count++;
				}
				else
					score->_data->text = "   " + high_scores[i];
			}
		}
	}

	static int enter_old_state = GLFW_RELEASE;
	int enter_state = glfwGetKey(glfw::window, GLFW_KEY_ENTER);

	if (enter_state == GLFW_RELEASE && enter_old_state == GLFW_PRESS)
	{
		std::cout << "ENTER" << std::endl;
		submit_score();
	}
	enter_old_state = enter_state;
}

void game_over_state::on_exit()
{
	glfwSetCharCallback(glfw::window, dummy_character_callback);
	glfwSetKeyCallback(glfw::window, dummy_key_callback);
	std::cout << "Exiting game over state" << std::endl;
}