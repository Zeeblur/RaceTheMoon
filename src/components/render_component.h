#pragma once

#include <iostream>
#include "../entity.h"
#include "component.h"
#include "../glfw.h"
#include "../opengl_util.h"
#include <glm/glm.hpp>

enum effectType
{
	simple,
	simple_texture,
	phong,
	text
};

struct render_component : public component
{
private:
    std::shared_ptr<gl::render_data> _data;

    std::shared_ptr<entity> _parent;
	GLuint programID;
public:
	render_component(std::shared_ptr<entity> e, std::shared_ptr<gl::render_data> data);

	bool initialise() override final;
	
	bool load_content() override final;
	
	void update(float delta_time) override final;
	
	void render() override final;
	 
	void unload_content() override final;
	
	void shutdown() override final;
}; 