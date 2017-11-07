//
// Created by zoe on 07/11/17.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../components/component.h"
#include "../subsystem.h"



class score_system : public subsystem
{
private:
    //std::vector<std::shared_ptr<camera_projection>> _data;

	score_system();

public:

    static inline std::shared_ptr<score_system> get()
    {
        static std::shared_ptr<score_system> instance = std::shared_ptr<score_system>(new score_system());
        return instance;
    }

    //std::shared_ptr<camera_component> build_component(std::shared_ptr<entity> e, camera_type type);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};