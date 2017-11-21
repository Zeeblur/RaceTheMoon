//
// Created by zoe on 11/10/17.
//

#include <ratio>
#include "physics_system.h"
#include "../thread_pool.h"

using namespace glm;

physics_system::physics_system()
{
    _visible = false;
    
}

std::shared_ptr<physics_component> physics_system::build_component(std::shared_ptr<entity> e)
{
	auto pd = std::make_shared<physics_data>(physics_data(e->get_trans()));

	_data.push_back(pd);
    return std::make_shared<physics_component>(e, pd);
}

std::shared_ptr<collider_component> physics_system::build_collider_component(std::shared_ptr<entity> e)
{
    auto ree = collider_data(e->get_trans());

    if (e->get_name() == "Bat")
    {

        std::shared_ptr<collider_data> cd = std::make_shared<collider_data>(collider_data(e->get_trans(), colType::PLAYER));

        _bat_collider = std::move(cd);
        return std::make_shared<collider_component>(e, std::ref(_bat_collider));
    }
    else
    {
        std::shared_ptr<collider_data> cd = std::make_shared<collider_data>(collider_data(e->get_trans(), colType::DAMAGE));

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::ref(_collider_data.back()));
    }
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

glm::vec3 check_radii(collider_base* col)
{
    glm::vec3 radii;

    if (auto aabb = static_cast<AABB*>(col))
    {
        for(int i = 0; i < 3; i++)
        {
            radii[i] = aabb->radius[i];
        }
    }
    else
    {
        auto sb = static_cast<sphere*>(col);
        for(int i = 0; i < 3; i++)
        {
            radii[i] = sb->radius;
        }
    }

    return radii;
}

bool is_colliding(collider_base* ac, collider_base* bc)
{

    glm::vec3 a_rad = check_radii(ac);
    glm::vec3 b_rad = check_radii(bc);

    if (abs(ac->centerPoint.x - bc->centerPoint.x) > a_rad[0] + b_rad[0])
        return false;
    if (abs(ac->centerPoint.y - bc->centerPoint.y) > a_rad[1] + b_rad[1])
        return false;
    if (abs(ac->centerPoint.z - bc->centerPoint.z) > a_rad[2] + b_rad[2])
        return false;

    std::cout << "Collision detected!" << std::endl;

    return true;
}

void moveTask(void* arg1, void* arg2)
{

    std::shared_ptr<physics_system> ps = physics_system::get();
    std::shared_ptr<physics_data> d = *static_cast<std::shared_ptr<physics_data>*>(arg1);
    float delta_time = *static_cast<float*> (arg2);

    // If active physics object add 1 to each component.

        //cap speed.
        ps->cap_speed(d->currentVelocity);

        // change by speed and delta-time.
        auto movement = d->currentVelocity * delta_time;

        // movement test here....
        d->x += movement.x;
        d->y += movement.y;
        d->z += movement.z;

        if (!d->moveRequest)
        {
            //std::cout << moveSpeed.x << ", " << moveSpeed.y << std::endl;
            // lateral movement
            if (d->currentVelocity.x < 0) d->currentVelocity.x += ps->deceleration.x;
            if (d->currentVelocity.x > 0) d->currentVelocity.x -= ps->deceleration.x;

            // if speed within epsilon of zero. Reset to zero
            if (d->currentVelocity.x > 0 && d->currentVelocity.x < ps->deceleration.x) d->currentVelocity.x = 0;
            if (d->currentVelocity.x < 0 && d->currentVelocity.x > -ps->deceleration.x) d->currentVelocity.x = 0;

            // vertical movement
            if (d->currentVelocity.y < 0) d->currentVelocity.y += ps->deceleration.y;
            if (d->currentVelocity.y > 0) d->currentVelocity.y -= ps->deceleration.y;

            // if speed within epsilon of zero. Reset to zero
            if (d->currentVelocity.y > 0 && d->currentVelocity.y < ps->deceleration.y) d->currentVelocity.y = 0;
            if (d->currentVelocity.y < 0 && d->currentVelocity.y > -ps->deceleration.y) d->currentVelocity.y = 0;

            // forwards movement
            if (d->currentVelocity.z < 0) d->currentVelocity.z += ps->deceleration.z;
            if (d->currentVelocity.z > 0) d->currentVelocity.z -= ps->deceleration.z;

            // if speed within epsilon of zero. Reset to zero
            if (d->currentVelocity.z > 0 && d->currentVelocity.z < ps->deceleration.z) d->currentVelocity.z = 0;
            if (d->currentVelocity.z < 0 && d->currentVelocity.z > -ps->deceleration.z) d->currentVelocity.z = 0;
        }
        else
        {
            std::cout << d->currentVelocity.y << std::endl;
        }

        // reset move request
        d->moveRequest = false;

}

void physics_system::update(float delta_time)
{
    //std::cout << "Physics system updating" << std::endl;
    for (auto &d : _data)
    {
        //push back task to list.
        if (d->active)
        {
            thread_pool::get()->add_job(thread_pool::get()->makeTask(moveTask, &d, &delta_time));
        }
    }

    while(thread_pool::get()->jd_.jobs_.size() != 0)
    {
        // wait on the threads to finish
    }

	// check bat against every other collider.
    for (size_t i = 0; i < _collider_data.size(); ++i)
    {
        bool col = is_colliding(_collider_data[i]->collider.get(), _bat_collider->collider.get());

        if (col)
        {
            engine::get()->get_subsystem("score_system")->hurt();
            break;
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
