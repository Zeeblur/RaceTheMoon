#pragma once

#include <iostream>
#include "entity.h"
#include "components/render_component.h"
#include "subsystem.h"

class renderer : public subsystem
{
private:
    std::vector<render_component*> _components;

	renderer();

public:

    inline static std::shared_ptr<renderer> get()
    {
        static std::shared_ptr<renderer> instance(new renderer());
        return instance;
    }

	std::shared_ptr<render_component> build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, effect effType, std::string mesh);
	
	bool initialise();

	bool load_content();

	void update(float delta_time);


    void render();


	void unload_content();
	void shutdown();


	GLuint programID;

};