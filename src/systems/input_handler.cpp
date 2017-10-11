//
// Created by zoe on 10/10/17.
//

#include "input_handler.h"


input_handler::input_handler()
{
    _visible = false;
}

std::shared_ptr<input_component> input_handler::build_component(std::shared_ptr<entity> e)
{
    //_data.push_back(input_component(e));
    return std::make_shared<input_component>(e);// std::ref(_data.back()));
}

bool input_handler::initialise()
{
    std::cout << "Input handler initialising" << std::endl;
    return true;
}

bool input_handler::load_content()
{
    std::cout << "Input handler loading content" << std::endl;
    return true;
}

void input_handler::update(float delta_time)
{
}

void input_handler::render()
{
    // This should never be called.
    std::cout << "Input handler rendering" << std::endl;
}

void input_handler::unload_content()
{
    std::cout << "Input handler unloading content" << std::endl;
}

void input_handler::shutdown()
{
    std::cout << "Input handler shutting down" << std::endl;
}