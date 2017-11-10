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

    auto up = glm::vec3(0.0f, 0.5f, 0.0f);
    aiUp_ = new MoveCommand(up);
    auto down = glm::vec3(0.0f, -0.5f, 0.0f);
    aiDown_ = new MoveCommand(down);
    auto forward = glm::vec3(0.0f, 0.0f, -0.5f);
    aiForward_ = new MoveCommand(forward);
    auto back = glm::vec3(0.0f, 0.0f, 0.5f);
    aiBack_ = new MoveCommand(back);
    auto right = glm::vec3(0.5f, 0.0f, 0.0f);
    aiRight_ = new MoveCommand(right);
    auto left = glm::vec3(-0.5f, 0.0f, 0.0f);
    aiLeft_ = new MoveCommand(left);

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

std::vector<Command*> ai_system::handle_ai(std::shared_ptr<ai_data> &d)
{
    std::vector<Command*> commands;
    auto target = d->distance + d->init_pos;
    auto current = d->cur_pos;
    auto endGap = glm::distance(target, current);
    auto startGap = glm::distance(d->init_pos, d->cur_pos);
    auto close = glm::length(glm::vec3(1.0f, 1.0f, 1.0f));

    /*std::cout << "\n Targ pos = (" << target.x << ", " << target.y << ", " << target.z << ")" <<
        "\t Cur pos = (" << current.x << ", " << current.y << ", " << current.z << ")" <<
        "\t End Gap = " << endGap <<
        "\t Close (should be 1) = " << close << std::endl;*/

    // ** UP THEN DOWN **
    if (d->ai_type == 0)
    {
        if (d->cur_pos.y < target.y && d->flagA == 0)
        {
            commands.push_back(aiUp_);
        }
        else if (d->cur_pos.y >= target.y && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.y > d->init_pos.y && d->flagA == 1)
        {
            commands.push_back(aiDown_);
        }
        else if (d->cur_pos.y <= d->init_pos.y && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

    // ** DOWN THEN UP **
    else if (d->ai_type == 1)
    {
        if (d->cur_pos.y > target.y && d->flagA == 0)
        {
            commands.push_back(aiDown_);
        }
        else if (d->cur_pos.y <= target.y && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.y < d->init_pos.y && d->flagA == 1)
        {
            commands.push_back(aiUp_);
        }
        else if (d->cur_pos.y >= d->init_pos.y && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

    // ** FORWARD THEN BACK **
    else if (d->ai_type == 2)
    {
        if (d->cur_pos.z > target.z && d->flagA == 0)
        {
            commands.push_back(aiForward_);
        }
        else if (d->cur_pos.z <= target.z && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.z < d->init_pos.z && d->flagA == 1)
        {
            commands.push_back(aiBack_);
        }
        else if (d->cur_pos.z >= d->init_pos.z && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

    // ** BACK THEN FORWARD **
    else if (d->ai_type == 3)
    {
        if (d->cur_pos.z < target.z && d->flagA == 0)
        {
            commands.push_back(aiBack_);
        }
        else if (d->cur_pos.z >= target.z && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.z > d->init_pos.z && d->flagA == 1)
        {
            commands.push_back(aiForward_);
        }
        else if (d->cur_pos.z <= d->init_pos.z && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

    // ** RIGHT THEN LEFT **
    else if (d->ai_type == 4)
    {
        if (d->cur_pos.x < target.x && d->flagA == 0)
        {
            commands.push_back(aiRight_);
        }
        else if (d->cur_pos.x >= target.x && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.x > d->init_pos.x && d->flagA == 1)
        {
            commands.push_back(aiLeft_);
        }
        else if (d->cur_pos.x <= d->init_pos.x && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

    // ** LEFT THEN RIGHT **
    else  if (d->ai_type == 5)
    {
        if (d->cur_pos.x > target.x && d->flagA == 0)
        {
            commands.push_back(aiLeft_);
        }
        else if (d->cur_pos.x <= target.x && d->flagA == 0)
        {
            d->flagA = 1;
        }
        else if (d->cur_pos.x < d->init_pos.x && d->flagA == 1)
        {
            commands.push_back(aiRight_);
        }
        else if (d->cur_pos.x >= d->init_pos.x && d->flagA == 1)
        {
            d->flagA = 0;
        }
    }

// OLD >>>>>>>>
    //// ** UP AND DOWN **
    //if (d->ai_type == 0)
    //{
    //    if (endGap > close)
    //    {
    //        commands.push_back(aiUp_);
    //    }
    //    else if (endGap < close)
    //    {
    //        d->ai_type = 1;
    //    }
    //}
    //else if (d->ai_type == 1)
    //{
    //    if (startGap > close)
    //    {
    //        commands.push_back(aiDown_);
    //    }
    //    else if (startGap < close)
    //    {
    //        d->ai_type = 0;
    //    }
    //}

    //// ** FORWARD AND BACK **
    //if (d->ai_type == 2)
    //{
    //    if (endGap > close)
    //    {
    //        commands.push_back(aiForward_);
    //    }
    //    else if (endGap < close)
    //    {
    //        d->ai_type = 3;
    //    }
    //}
    //else if (d->ai_type == 3)
    //{
    //    if (startGap > close)
    //    {
    //        commands.push_back(aiBack_);
    //    }
    //    else if (startGap < close)
    //    {
    //        d->ai_type = 2;
    //    }
    //}

    //// ** RIGHT THEN LEFT **
    //if (d->ai_type == 4)
    //{
    //    if (endGap > close)
    //    {
    //        commands.push_back(aiRight_);
    //    }
    //    else if (endGap < close)
    //    {
    //        d->ai_type = 5;
    //    }
    //}
    //else if (d->ai_type == 5)
    //{
    //    if (startGap > close)
    //    {
    //        commands.push_back(aiLeft_);
    //    }
    //    else if (startGap < close)
    //    {
    //        d->ai_type = 4;
    //    }
    //}

    // ** SUN AND MOON **
    else if (d->ai_type == 6)
    {
        commands.push_back(aiUp_);
    }

    return commands;
}
