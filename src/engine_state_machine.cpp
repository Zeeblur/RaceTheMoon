#include "engine_state_machine.h"
#include "entity_manager.h"
#include "systems/clickable_system.h"


engine_state_machine::engine_state_machine()
{
    _visible = false;
}

std::shared_ptr<engine_state_machine> engine_state_machine::get()
{
    static std::shared_ptr<engine_state_machine> instance(new engine_state_machine());
    return instance;
}

void engine_state_machine::add_state(const std::string &name, std::shared_ptr<engine_state> state, state_type type)
{
    state->type = type;
    _states[name] = state;
}



void engine_state_machine::change_state(const std::string &name, bool reset)
{
    if (name != _current_state_name)
    {
        auto found = _states.find(name);
        if (found != _states.end())
        {
            if (_current_state != nullptr)
                _current_state->on_exit();
            _current_state = found->second;

			if (reset)
				_current_state->on_reset();

            _current_state->on_enter();
            _current_state_name = name;
            _current_state_type = _current_state->type;

            entity_manager::get()->currentState = _current_state_type;
        }
        else
        {
            throw std::invalid_argument("state not found");
        }
    }
}

std::string engine_state_machine::get_current_state()
{
    return _current_state_name;
}

state_type engine_state_machine::get_current_state_type()
{
    return _current_state_type;
}

bool engine_state_machine::initialise()
{
	for (auto &s : _states)
	{
		s.second->initialise();
	}
    return true;
}

bool engine_state_machine::load_content()
{
    return true;
}

void engine_state_machine::update(float delta_time)
{
	static float total_time;
	total_time += delta_time;
	//std::cout << total_time << std::endl;
	// Add an interval for checking click events, avoid accidental clicking of buttons when switching states
	if (total_time >= 0.25f)
	{
		if (engine_state_machine::get()->get_current_state_type() == state_type::MENU)
		{
			//std::cout << "=============MENU STATE============" << std::endl;
			std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));
			if (cs->get_clicked_component_name() == "buttonPlay")
			{
				std::cout << "Test" << std::endl;
				engine_state_machine::get()->change_state("game_state", true);
				cs->clear_clicked_component_name();
				total_time = 0;
			}
			else if (cs->get_clicked_component_name() == "buttonExit")
			{
				// Handle exit game logic here
				engine::get()->set_running(false);
				cs->clear_clicked_component_name();
				total_time = 0;
			}

		}
		else if (engine_state_machine::get()->get_current_state_type() == state_type::PAUSE)
		{
			std::shared_ptr<clickable_system> cs = std::static_pointer_cast<clickable_system>(engine::get()->get_subsystem("clickable_system"));
			if (cs->get_clicked_component_name() == "buttonContinue")
			{
				engine_state_machine::get()->change_state("game_state");
				cs->clear_clicked_component_name();
				total_time = 0;
			}
			else if (cs->get_clicked_component_name() == "buttonMenu")
			{
				engine_state_machine::get()->change_state("menu_state");
				cs->clear_clicked_component_name();
				total_time = 0;
			}
		}
	}
    static int escape_old_state = GLFW_RELEASE;
    int escape_state = glfwGetKey(glfw::window, GLFW_KEY_ESCAPE);

    if (escape_state == GLFW_RELEASE && escape_old_state == GLFW_PRESS)
    {
        switch (engine_state_machine::get()->get_current_state_type())
        {
            // Go from game state to pause state
        case state_type::GAME:
            engine_state_machine::get()->change_state("pause_state");
            break;
            // Go from pause state to game state
        case state_type::PAUSE:
            engine_state_machine::get()->change_state("game_state");
            break;
		case state_type::GAME_OVER:
			engine_state_machine::get()->change_state("menu_state");
			break;
        default:
            // do nothing
            break;
        }
    }
    escape_old_state = escape_state;

    static int enter_old_state = GLFW_RELEASE;
    int enter_state = glfwGetKey(glfw::window, GLFW_KEY_ENTER);

    if (enter_state == GLFW_RELEASE && enter_old_state == GLFW_PRESS)
    {
        switch (engine_state_machine::get()->get_current_state_type())
        {
            // Go from menu state to game state RESETTING GAME
        case state_type::MENU:
            engine_state_machine::get()->change_state("game_state", true);
            break;
		case state_type::GAME_OVER:
			engine_state_machine::get()->change_state("menu_state");
			break;
        default:
            // do nothing
            break;
        }
    }
    enter_old_state = enter_state;

    static int backspace_old_state = GLFW_RELEASE;
    int backspace_state = glfwGetKey(glfw::window, GLFW_KEY_BACKSPACE);

    if (backspace_state == GLFW_RELEASE && backspace_old_state == GLFW_PRESS)
    {
        switch (engine_state_machine::get()->get_current_state_type())
        {
            // Go from pause state to menu state
        case state_type::PAUSE:
            engine_state_machine::get()->change_state("menu_state");
            break;
		case state_type::GAME_OVER:
			engine_state_machine::get()->change_state("menu_state");
			break;
        default:
            // do nothing
            break;
        }
    }
    backspace_old_state = backspace_state;

    if (_current_state != nullptr)
        _current_state->on_update(delta_time);

}

void engine_state_machine::render()
{

}

void engine_state_machine::unload_content()
{

}

void engine_state_machine::shutdown()
{

}
