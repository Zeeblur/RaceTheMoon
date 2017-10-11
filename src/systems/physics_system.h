#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../component.h"
#include "../subsystem.h"


#include "../components/physics_component.h"

class physics_system : public subsystem
{
private:
    std::vector<physics_data> _data;

    physics_system();

    void cap_speed(glm::vec3& currentSpeed);

    // move scale is scaled by framerate
    float moveScale = 60.0f;

    glm::vec3 acceleration = glm::vec3(0.2f * moveScale);
    glm::vec3 deceleration = glm::vec3(0.4f * moveScale);

public:

    static inline std::shared_ptr<physics_system> get()
    {
        static std::shared_ptr<physics_system> instance = std::shared_ptr<physics_system>(new physics_system());
        return instance;
    }

    std::shared_ptr<physics_component> build_component(std::shared_ptr<entity> e);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;

    float maxSpeed = 2.0f * moveScale;
};