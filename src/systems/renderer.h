#pragma once

#include <iostream>
#include "../entity.h"
#include "../opengl_util.h"
#include "../components/render_component.h"
#include "../subsystem.h"
#include "../components/light_component.h"

class renderer : public subsystem
{
private:
	std::map<effectType, std::shared_ptr<gl::Effect>> programIDs;
	std::map<std::string, std::shared_ptr<gl::texture>> textureList;

    renderer();
public:

    inline static std::shared_ptr<renderer> get()
    {
        static std::shared_ptr<renderer> instance(new renderer());
        return instance;
    }

    std::shared_ptr<render_component> build_component(std::shared_ptr<entity> &e, glm::vec4 colour, std::string texture_path, std::string shape, std::string shader, effectType effType);


	std::shared_ptr<light_component> build_light(std::shared_ptr<entity> &e);

	void change_texture(const std::shared_ptr<entity> &e, std::string texture_path);

    bool initialise();

    bool load_content();

    void update(float delta_time);

    void render();

    void unload_content();

	void shutdown();

	std::vector<std::shared_ptr<gl::render_data>> _dataList;
	std::vector<std::shared_ptr<gl::render_data>> _dataText;
};