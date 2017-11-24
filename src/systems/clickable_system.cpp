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

std::shared_ptr<clickable_component> clickable_system::build_component(std::shared_ptr<entity> e, glm::dvec2 center, glm::dvec2 scale)
{
    _data.push_back(clickable_data());
	_data.back().center = center;
	_data.back().scale = scale;
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
			transform_data td = entity_manager::get()->get_entity(d.parent_name)->get_trans();
			//int x_center;
			//int y_center;
			//glfwGetWindowSize(glfw::window, &x_center, &y_center);

			//std::cout << "x: " << td.x << " y: " << td.y << "z: " << td.z << std::endl;
			//// x bounds min
			//d.x_bounds.x = td.x - (td.scale.x / 2);
			//// x bounds max
			//d.x_bounds.y = td.x + (td.scale.x / 2);
			//// y bounds min
			//d.y_bounds.x = td.y - (td.scale.y / 2);
			//// y bounds max
			//d.y_bounds.y = td.y + (td.scale.y / 2);

			int x_min = d.center.x - d.scale.x;
			int x_max = d.center.x + d.scale.x;
			int y_min = d.center.y - d.scale.y;
			int y_max = d.center.y + d.scale.y;

            if (state == GLFW_PRESS && x_pos >= x_min && x_pos <= x_max && y_pos >= y_min && y_pos <= y_max
				&& engine_state_machine::get()->get_current_state_type() == entity_manager::get()->get_entity(d.parent_name)->state)
            {
				audio_system::get()->play_sound(button_press);
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

