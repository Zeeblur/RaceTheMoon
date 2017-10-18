//
// Created by zoe on 11/10/17.
//

#include "physics_system.h"

using namespace glm;

physics_system::physics_system()
{
    _visible = false;
}

std::shared_ptr<physics_component> physics_system::build_component(std::shared_ptr<entity> e)
{
    _data.push_back(physics_data());
    return std::make_shared<physics_component>(e, std::ref(_data.back()));
}

bool physics_system::initialise()
{
    std::cout << "Physics system initialising" << std::endl;
    return true;
}

bool physics_system::load_content()
{
    std::cout << "Physics system loading content" << std::endl;
    return true;
}

void physics_system::update(float delta_time)
{
    //std::cout << "Physics system updating" << std::endl;
    for (auto &d : _data)
    {
        // If active physics object add 1 to each component.
        if (d.active)
        {
            //cap speed.
            cap_speed(d.currentVelocity);

            // change by speed and delta-time.
            auto movement = d.currentVelocity * delta_time;

            // movement test here....
            d.x += movement.x;
            d.y += movement.y;
            d.z += movement.z;

            if (!d.moveRequest)
            {
                //std::cout << moveSpeed.x << ", " << moveSpeed.y << std::endl;
                // lateral movement
                if (d.currentVelocity.x < 0) d.currentVelocity.x += deceleration.x;
                if (d.currentVelocity.x > 0) d.currentVelocity.x -= deceleration.x;

                // if speed within epsilon of zero. Reset to zero
                if (d.currentVelocity.x > 0 && d.currentVelocity.x < deceleration.x) d.currentVelocity.x = 0;
                if (d.currentVelocity.x < 0 && d.currentVelocity.x > -deceleration.x) d.currentVelocity.x = 0;

                // forwards movement
                if (d.currentVelocity.z < 0) d.currentVelocity.z += deceleration.z;
                if (d.currentVelocity.z > 0) d.currentVelocity.z -= deceleration.z;

                // if speed within epsilon of zero. Reset to zero
                if (d.currentVelocity.z > 0 && d.currentVelocity.z < deceleration.z) d.currentVelocity.z = 0;
                if (d.currentVelocity.z < 0 && d.currentVelocity.z > -deceleration.z) d.currentVelocity.z = 0;
            }

            // reset move request
            d.moveRequest = false;
        }
    }
}

void physics_system::cap_speed(vec3& currentSpeed)
{
    // limit movement

    if (currentSpeed.x > maxSpeed) currentSpeed.x = maxSpeed;
    if (currentSpeed.x < -maxSpeed) currentSpeed.x = -maxSpeed;
    if (currentSpeed.y > maxSpeed) currentSpeed.y = maxSpeed;
    if (currentSpeed.y < -maxSpeed) currentSpeed.y = -maxSpeed;
    if (currentSpeed.z > maxSpeed) currentSpeed.z = maxSpeed;
    if (currentSpeed.z < -maxSpeed) currentSpeed.z = -maxSpeed;

}

void physics_system::render()
{
    // This should never be called.
    std::cout << "Physics system rendering" << std::endl;
}

void physics_system::unload_content()
{
    std::cout << "Physics system unloading content" << std::endl;
}

void physics_system::shutdown()
{
    std::cout << "Physics system shutting down" << std::endl;
}
