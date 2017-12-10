//
// Created by zoe on 07/11/17.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../components/component.h"
#include "../components/score_component.h"
#include "../subsystem.h"



class score_system : public subsystem
{
private:


	score_system();

	float totalTime = 0;
	int seconds = 0;
public:
	std::vector<std::shared_ptr<score_data>> _data;
    static inline std::shared_ptr<score_system> get()
    {
        static std::shared_ptr<score_system> instance = std::shared_ptr<score_system>(new score_system());
        return instance;
    }

    std::shared_ptr<score_component> build_component(std::shared_ptr<entity> e);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;

    void hurt();

    void addScore();

    void addPointsPowerUp();
};