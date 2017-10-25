#pragma once

#include <iostream>
#include "entity.h"
#include "components/render_component.h"
#include "subsystem.h"

class renderer : public subsystem
{
private:
    renderer();

	GLuint vertexbuffer;

public:

    inline static std::shared_ptr<renderer> get()
    {
        static std::shared_ptr<renderer> instance(new renderer());
        return instance;
    }

    std::shared_ptr<render_component> build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, effect effType);

    bool initialise();

    bool load_content();

    void update(float delta_time);

    void render();

    void unload_content();

	void shutdown();

    GLuint programID;

	std::vector<std::shared_ptr<render_data>> _dataList;

};