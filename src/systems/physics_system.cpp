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
	auto pd = std::make_shared<physics_data>(physics_data(e->get_trans()));

	_data.push_back(pd);
    return std::make_shared<physics_component>(e, pd);
}

std::shared_ptr<collider_component> physics_system::build_collider_component(std::shared_ptr<entity> e)
{
	_collider_data.push_back(collider_data());
	return std::make_shared<collider_component>(e, std::ref(_collider_data.back()));
}

std::shared_ptr<collider_component> physics_system::build_collider_component(std::shared_ptr<entity> e, glm::vec3 scale)
{
	_collider_data.push_back(collider_data());
	_collider_data.back().collider.radius[0] = scale.x;
	_collider_data.back().collider.radius[1] = scale.y;
	_collider_data.back().collider.radius[2] = scale.z;
	return std::make_shared<collider_component>(e, std::ref(_collider_data.back()));
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


// AABB against AABB collision
bool is_colliding(const AABB &a, const AABB &b)
{
	if (abs(a.centerPoint.x - b.centerPoint.x) > a.radius[0] + b.radius[0])
		return false;
	if (abs(a.centerPoint.y - b.centerPoint.y) > a.radius[1] + b.radius[1])
		return false;
	if (abs(a.centerPoint.z - b.centerPoint.z) > a.radius[2] + b.radius[2])
		return false;

	std::cout << "Collision detected!" << std::endl;

	return true;
}

void physics_system::update(float delta_time)
{
    //std::cout << "Physics system updating" << std::endl;
    for (auto &d : _data)
    {
        // If active physics object add 1 to each component.
        if (d->active)
        {
            //cap speed.
            cap_speed(d->currentVelocity);

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
                if (d->currentVelocity.x < 0) d->currentVelocity.x += deceleration.x;
                if (d->currentVelocity.x > 0) d->currentVelocity.x -= deceleration.x;

                // if speed within epsilon of zero. Reset to zero
                if (d->currentVelocity.x > 0 && d->currentVelocity.x < deceleration.x) d->currentVelocity.x = 0;
                if (d->currentVelocity.x < 0 && d->currentVelocity.x > -deceleration.x) d->currentVelocity.x = 0;

                // forwards movement
                if (d->currentVelocity.z < 0) d->currentVelocity.z += deceleration.z;
                if (d->currentVelocity.z > 0) d->currentVelocity.z -= deceleration.z;

                // if speed within epsilon of zero. Reset to zero
                if (d->currentVelocity.z > 0 && d->currentVelocity.z < deceleration.z) d->currentVelocity.z = 0;
                if (d->currentVelocity.z < 0 && d->currentVelocity.z > -deceleration.z) d->currentVelocity.z = 0;
            }

            // reset move request
            d->moveRequest = false;
        }
    }
	// Don't bother checking for collisions unless there are at least 2 colliders
	if (_collider_data.size() >= 2)
	{
		// Check for collisions
		for (size_t i = 0; i < _collider_data.size() - 1; ++i)
		{
			is_colliding(_collider_data[i].collider, _collider_data[i + 1].collider);
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
