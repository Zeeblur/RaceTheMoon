#pragma once

#include <iostream>
#include "../entity.h"
#include "component.h"
#include "../glfw.h"
#include "../opengl_util.h"
#include <glm/glm.hpp>

// Effect struct
struct Effect
{
	std::string name;
	bool has_geometry;
	bool is_compute;
	void *GpuData;
};

enum effect
{
	simple
};


struct render_data
{
	bool visible;// = true;
	// Let's pretend this is a matrix that was built.
	std::string colour;// = "Red";
	std::string shader;// = "Phong";

	glm::mat4 MVP;

	// Reference to structs
	Effect* effect;

	// shape is now mesh
	std::shared_ptr<gl::mesh_geom> mesh;
};

struct render_component : public component
{
private:
    std::shared_ptr<render_data> _data;

    std::shared_ptr<entity> _parent;
	GLuint programID;
public:
	render_component(std::shared_ptr<entity> e, std::shared_ptr<render_data> data);

	bool initialise() override final;
	
	bool load_content() override final;
	
	void update(float delta_time) override final;
	
	void render() override final;
	 
	void unload_content() override final;
	
	void shutdown() override final;
}; 