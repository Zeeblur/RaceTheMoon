//
// Created by zoe on 18/10/17.
//

#include "camera_system.h"

camera_system::camera_system()
{
	_visible = false;
}

std::shared_ptr<camera_component> camera_system::build_component(std::shared_ptr<entity> e, camera_type type)
{
	camera_projection proj;
	int width = 0, height = 0;
	glfwGetWindowSize(glfw::window, &width, &height);

	switch (type)
	{
	case camera_type::CHASE:
		proj.fov = 1.0472f;
		proj.aspect = (16.0f / 9.0f);
		proj.near = 0.01f;
		proj.far = 1000.0f;
		proj.type = CHASE;
		break;
	case camera_type::ORTHO:
		proj.fov = 1.0472f;
		proj.aspect = (16.0f / 9.0f);
		proj.near = -1000.0f;
		proj.far = 1000.0f;
		proj.left = -0.5f * (float)width;
		proj.bottom = -0.5f * (float)height;
		proj.type = ORTHO;
		break;
	}

	_data.push_back(std::make_shared<camera_projection>(proj));
	return std::make_shared<camera_component>(e, std::ref(_data.back()));
}

bool camera_system::initialise()
{
	std::cout << "Camera system initialising" << std::endl;
	return true;
}

bool camera_system::load_content()
{
	std::cout << "Camera system loading content" << std::endl;
	return true;
}

void camera_system::update(float delta_time)
{

	// may need to update modelview
	for (auto &c : _data)
	{
		switch (c->type)
		{
		case camera_type::CHASE:
			player_cam_MV = c->model_view;
			break;
		case camera_type::ORTHO:
			break;
		}
	}
}

void camera_system::render()
{
	// This should never be called.
	std::cout << "Camera system rendering" << std::endl;
}

void camera_system::unload_content()
{
	std::cout << "Camera system unloading content" << std::endl;
}

void camera_system::shutdown()
{
	std::cout << "Camera system shutting down" << std::endl;
}