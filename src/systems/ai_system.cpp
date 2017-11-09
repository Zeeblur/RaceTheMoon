//
// Created by beej on 09/11/17.
//

#include "ai_system.h"

#include "../entity_manager.h"


ai_system::ai_system()
{
    _visible = false;
}

std::shared_ptr<ai_component> ai_system::build_component(std::shared_ptr<entity> e, unsigned int ai_type, vec3 distance)
{
    auto _ad = std::make_shared<ai_data>();

    _ad->ai_type = ai_type;
    _ad->distance = distance;
    _ad->init_pos = glm::vec3(e->get_trans().x, e->get_trans().y, e->get_trans().z);
    _ad->cur_pos = glm::vec3(e->get_trans().x, e->get_trans().y, e->get_trans().z);

    _ai_data.push_back(_ad);

    // create input component and pass in the handler instance
    return std::make_shared<ai_component>(e, _ad);
}

bool ai_system::initialise()
{
    std::cout << "Input handler initialising" << std::endl;

    //map buttons

    auto up = glm::vec3(0.0f, 1.0f, 0.0f);
    aiUp_ = new MoveCommand(up);

    auto down = glm::vec3(0.0f, -1.0f, 0.0f);


    return true;
}

bool ai_system::load_content()
{
    std::cout << "Input handler loading content" << std::endl;
    return true;
}

void ai_system::update(float delta_time)
{
}

void ai_system::render()
{
    // This should never be called.
    std::cout << "Input handler rendering" << std::endl;
}

void ai_system::unload_content()
{
    std::cout << "Input handler unloading content" << std::endl;
}

void ai_system::shutdown()
{
    std::cout << "Input handler shutting down" << std::endl;
}

std::vector<Command*> ai_system::handle_input()
{
    std::vector<Command*> commands;
	
    return commands;
}

std::vector<Command*> ai_system::handle_ai(std::shared_ptr<ai_data> &d)
{

    std::vector<Command*> commands;
    auto target = glm::distance(d->distance, d->init_pos);
    auto current = glm::distance(d->init_pos, d->cur_pos);


   // auto current = d->cur_pos.y;

    //std::cout << "cur pos : " << current << std::endl;

    // get initial positon from parent
    if (d->ai_type == 0 && current < target)
    {
        commands.push_back(aiUp_);
    }
    return commands;

}
