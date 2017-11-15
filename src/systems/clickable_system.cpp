#include "clickable_system.h"
#include "../glfw.h"
#include "../engine_state_machine.h"
#include "../entity_manager.h"
clickable_system::clickable_system()
{
    _visible = false;
}

std::shared_ptr<clickable_system> clickable_system::get()
{
    static std::shared_ptr<clickable_system> instance = std::shared_ptr<clickable_system>(new clickable_system());
    return instance;
}

std::shared_ptr<clickable_component> clickable_system::build_component(std::shared_ptr<entity> e, glm::dvec2 x_bounds, glm::dvec2 y_bounds)
{
    _data.push_back(clickable_data());
    _data.back().x_bounds = x_bounds;
    _data.back().y_bounds = y_bounds;
    _data.back().parent_name = e->get_name();
    return std::make_shared<clickable_component>(e, std::ref(_data.back()));
}

bool clickable_system::initialise()
{
    std::cout << "Clickable system initialising" << std::endl;
    return true;
}

bool clickable_system::load_content()
{
    std::cout << "Clickable system loading content" << std::endl;
    return true;
}

void clickable_system::update(float delta_time)
{
    for (auto &d : _data)
    {
        // If active check for click
        if (d.active)
        {
            double x_pos = 0;
            double y_pos = 0;

            glfwGetCursorPos(glfw::window, &x_pos, &y_pos);

            int state = glfwGetMouseButton(glfw::window, GLFW_MOUSE_BUTTON_LEFT);

            if (state == GLFW_PRESS && x_pos >= d.x_bounds.x && x_pos <= d.x_bounds.y && y_pos >= d.y_bounds.x && y_pos <= d.y_bounds.y 
				&& engine_state_machine::get()->get_current_state_type() == entity_manager::get()->get_entity(d.parent_name)->state)
            {
				audio_system::get()->play_one_shot("res/sounds/click.wav", 1);
                std::cout << "Clicked button with name: " << d.parent_name << std::endl;
                // Save currently clicked component
                _latest_clicked_component = d.parent_name;
                d.clicks++;
            }
        }
    }
}

std::string clickable_system::get_clicked_component_name()
{
    return _latest_clicked_component;
}

void clickable_system::clear_clicked_component_name()
{
    _latest_clicked_component = "";
}

void clickable_system::render()
{
}

void clickable_system::unload_content()
{
    std::cout << "Clickable system unloading content" << std::endl;
}

void clickable_system::shutdown()
{
    std::cout << "Clickable system shutting down" << std::endl;
}

