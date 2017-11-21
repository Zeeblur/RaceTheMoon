#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../components/component.h"
#include "../subsystem.h"
#include "../components/physics_component.h"
#include "../components/collider_component.h"
#include "../entity_manager.h"
#include "score_system.h"

class physics_system : public subsystem
{
private:
    std::vector<std::shared_ptr<physics_data>> _data;

	std::vector<std::shared_ptr<collider_data>> _collider_data;

    std::shared_ptr<collider_data> _bat_collider;

    physics_system();



public:

    void cap_speed(glm::vec3& currentSpeed);


    // move scale is scaled by framerate
    float moveScale = 60.0f;

    glm::vec3 acceleration = glm::vec3(0.2f * moveScale);
    glm::vec3 deceleration = glm::vec3(0.4f * moveScale);

    static inline std::shared_ptr<physics_system> get()
    {
        static std::shared_ptr<physics_system> instance = std::shared_ptr<physics_system>(new physics_system());
        return instance;
    }

    std::shared_ptr<physics_component> build_component(std::shared_ptr<entity> e);

	std::shared_ptr<collider_component> build_collider_component(std::shared_ptr<entity> e);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;

    //void moveTask(void* arg1, void* arg2);
    ///void moveTask(const std::shared_ptr<physics_data> d, float delta_time);

    float maxSpeed = 2.0f * moveScale;
};