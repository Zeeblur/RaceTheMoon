#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../components/component.h"
#include "../subsystem.h"
#include "../components/camera_component.h"

enum camera_type
{
	FREE,
	ORTHO,
};

class camera_system : public subsystem
{
private:
    std::vector<camera_projection> _data;

    camera_system();

public:

    static inline std::shared_ptr<camera_system> get()
    {
        static std::shared_ptr<camera_system> instance = std::shared_ptr<camera_system>(new camera_system());
        return instance;
    }

    std::shared_ptr<camera_component> build_component(std::shared_ptr<entity> e, camera_type type);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};