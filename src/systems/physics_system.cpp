//
// Created by zoe on 11/10/17.
//

#include <ratio>
#include "physics_system.h"
#include "../thread_pool.h"

using namespace glm;

bool increasedSpeed = false;

physics_system::physics_system()
{
    _visible = false;
    
}

std::shared_ptr<physics_component> physics_system::build_component(std::shared_ptr<entity> e)
{
    if (e->get_name() == "Bat")
    {
        auto pd = std::make_shared<physics_data>(physics_data(e->get_trans(), "Bat"));

        _data.push_back(std::ref(pd));
        return std::make_shared<physics_component>(e, pd);
    }
    else
    {
        auto pd = std::make_shared<physics_data>(physics_data(e->get_trans()));

        _data.push_back(std::ref(pd));
        return std::make_shared<physics_component>(e, pd);
    }
}

std::shared_ptr<physics_component> physics_system::build_component(std::shared_ptr<entity> e, std::shared_ptr<physics_data> d)
{

	//_data.push_back(d);
	return std::make_shared<physics_component>(e, d);
}

std::shared_ptr<collider_component> physics_system::build_collider_component(std::shared_ptr<entity> e, colType c)
{
    auto ree = e->get_trans();

    // Sort incoming collider components into respective physics_system collider data
    if (c == colType::PLAYER)
    {
        std::shared_ptr<collider_data> cd = std::make_shared<collider_data>(e->get_trans(), colType::PLAYER, e->get_name());

        _bat_collider = std::ref(cd);
        return std::make_shared<collider_component>(e, _bat_collider);
    }
    else if (c == colType::DAMAGE)
    {
        auto cd = std::make_shared<collider_data>(e->get_trans(), colType::DAMAGE, e->get_name());

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::move(cd));
    }
    else if (c == colType::SHIELD)
    {
        auto cd = std::make_shared<collider_data>(e->get_trans(), colType::SHIELD, e->get_name());

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::move(cd));
    }
    else if (c == colType::POINTS)
    {
        auto cd = std::make_shared<collider_data>(e->get_trans(), colType::POINTS, e->get_name());

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::move(cd));
    }
    else if (c == colType::MINIBAT)
    {
        auto cd = std::make_shared<collider_data>(e->get_trans(), colType::MINIBAT, e->get_name());

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::move(cd));
    }
    else if (c == colType::SPEED)
    {
        auto cd = std::make_shared<collider_data>(e->get_trans(), colType::SPEED, e->get_name());

        _collider_data.push_back(cd);
        return std::make_shared<collider_component>(e, std::move(cd));
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

    if (auto aabb = dynamic_cast<AABB*>(col))
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

        // reset move request
        d->moveRequest = false;

}

void collision(void* col1, void* batCol)
{
    auto &_obstacle = *static_cast<shared_ptr<collider_data>*>(col1);
    auto &_bat_collider = *static_cast<shared_ptr<collider_data>*>(batCol);

    std::shared_ptr<physics_system> ps = physics_system::get();
    auto data = ps->_data;
    //float delta_time = *static_cast<float*> (arg2);

    // Is player bat colliding with something
    bool col = is_colliding(_obstacle->collider.get(), _bat_collider->collider.get());

    // Obstacle collision without shield
    if (col && _bat_collider->shield == false && _obstacle->behaviour_ == colType::DAMAGE)
    {
        for (auto &d : data)
        {
            if (d->name_ == "Bat")
            {
                d->currentVelocity -= d->currentVelocity;
            }
        }
        engine::get()->get_subsystem("score_system")->hurt();
    }
    // Obstacle collision with shield
    else if (col && _bat_collider->shield == true && _obstacle->behaviour_ == colType::DAMAGE)
    {
        _bat_collider->timeOfShield++;
    }
    // Shield power-up collision
    else if (col && _obstacle->behaviour_ == colType::SHIELD)
    {
        entity_manager::get()->delete_entity(_obstacle->name_);
        _bat_collider->shield = true;
    }
    // Points power-up collision
    else if (col && _obstacle->behaviour_ == colType::POINTS)
    {
        entity_manager::get()->delete_entity(_obstacle->name_);
        engine::get()->get_subsystem("score_system")->addPointsPowerUp();
    }
    // Minibat power-up collision
    else if (col && _obstacle->behaviour_ == colType::MINIBAT)
    {
        entity_manager::get()->delete_entity(_obstacle->name_);
        _bat_collider->shrunk = true;

    }
    // Speed power-up collision
    else if (col && _obstacle->behaviour_ == colType::SPEED)
    {
        entity_manager::get()->delete_entity(_obstacle->name_);
        _bat_collider->speedTimer = 0.0f;
        _bat_collider->speed = true;
    }
}

void physics_system::update(float delta_time)
{
    static bool isShrinking = false;
    static bool isShrunk = false;
    static float shrinkingTimer = 0.0f;
    static float totalShrinking = 2.0f;
    //std::cout << "Physics system updating" << std::endl;
    for (auto &d : _data)
    {
        //push back task to list.
        if (d->active)
        {
            thread_pool::get()->add_job(thread_pool::get()->makeTask(moveTask, &d, &delta_time));
        }
    }
    for (auto &c : _collider_data)
    {
        if (!c.expired())
            thread_pool::get()->add_job(thread_pool::get()->makeTask(collision, &c, &_bat_collider));
    }
    // If collisions have happened for long enough, remove shield
    if (_bat_collider->timeOfShield > 50.0f)
        _bat_collider->shield = false;

    // Superspeed lasts 3 seconds
    if (_bat_collider->speed)
    {
        for (auto &d : _data)
        {
            if (d->name_ == "Bat")
            {
                d->currentVelocity.z -= maxSpeed;
            }
        }
        _bat_collider->speedTimer += delta_time;
    }
    if (_bat_collider->speedTimer > 3.0f)
    {
        _bat_collider->speed = false;
        _bat_collider->speedTimer = 0.0f;
    }

    // ** Shrinking animation **
    if (_bat_collider->shrunk == true)
    {
        isShrinking = true;
        shrinkingTimer += delta_time;
        _bat_collider->shrunk = false;
    }
    if (isShrinking == true && shrinkingTimer && shrinkingTimer < ((1.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrinking == true && shrinkingTimer >= ((1.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((2.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (isShrinking == true && shrinkingTimer >= ((2.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((3.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrinking == true && shrinkingTimer >= ((3.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((4.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (isShrinking == true && shrinkingTimer >= ((4.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((5.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrinking == true && shrinkingTimer >= ((5.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((8.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.4f, 0.4f, 0.4f);
    }
    if (isShrinking == true && shrinkingTimer >= ((8.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((11.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.3f, 0.3f, 0.3f);
    }
    if (isShrinking == true && shrinkingTimer >= ((11.0f / 15.0f) * totalShrinking) && shrinkingTimer < ((14.0f / 15.0f) * totalShrinking))
    {
        shrinkingTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (isShrinking == true && shrinkingTimer >= ((14.0f / 15.0f) * totalShrinking))
    {
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
        shrinkingTimer = 0.0f;
        isShrinking = false;
        isShrunk = true;
    }
    
    // If shrunk for long enough, resize animation 
    if (isShrunk == true && _bat_collider->shrunkTimer < ((30.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((30.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((32.0f / 15.0f)* totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((32.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((34.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((34.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((36.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((36.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((38.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.2f, 0.2f, 0.2f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((38.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((40.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.3f, 0.3f, 0.3f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((40.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((42.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.4f, 0.4f, 0.4f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((42.0f / 15.0f) * totalShrinking) && _bat_collider->shrunkTimer < ((44.0f / 15.0f) * totalShrinking))
    {
        _bat_collider->shrunkTimer += delta_time;
        entity_manager::get()->get_entity("Bat")->get_trans().scale = glm::vec3(0.5f, 0.5f, 0.5f);
    }
    if (isShrunk == true && _bat_collider->shrunkTimer >= ((44.0f / 15.0f) * totalShrinking))
    {
        isShrunk = false;
        _bat_collider->shrunkTimer = 0.0f;
    }
    // ** end of animation ** 
}

void physics_system::cap_speed(vec3& currentSpeed)
{
    // limit movement

    if (_bat_collider->speed == false)
    {
        if (currentSpeed.x > maxSpeed) currentSpeed.x = maxSpeed;
        if (currentSpeed.x < -maxSpeed) currentSpeed.x = -maxSpeed;
        if (currentSpeed.y > maxSpeed) currentSpeed.y = maxSpeed;
        if (currentSpeed.y < -maxSpeed) currentSpeed.y = -maxSpeed;
        if (currentSpeed.z > maxSpeed) currentSpeed.z = maxSpeed;
        if (currentSpeed.z < -maxSpeed) currentSpeed.z = -maxSpeed;
    }
    else if (_bat_collider->speed == true)
    {
        float superSpeed = maxSpeed * 2;
        if (currentSpeed.x > superSpeed) currentSpeed.x = superSpeed;
        if (currentSpeed.x < -superSpeed) currentSpeed.x = -superSpeed;
        if (currentSpeed.y > superSpeed) currentSpeed.y = superSpeed;
        if (currentSpeed.y < -superSpeed) currentSpeed.y = -superSpeed;
        if (currentSpeed.z > superSpeed) currentSpeed.z = superSpeed;
        if (currentSpeed.z < -superSpeed) currentSpeed.z = -superSpeed;
    }

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
