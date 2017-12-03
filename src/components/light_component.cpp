//
// Created by zoe on 24/10/17.
//
#define GLM_ENABLE_EXPERIMENTAL
#include "light_component.h"

light_component::light_component(std::shared_ptr<entity> &e, std::shared_ptr<gl::light_data> &data) : _parent(e), _light(data)
{
	_position = glm::vec3(e->get_trans().x, e->get_trans().y, e->get_trans().z);
}

bool light_component::initialise() { return true; }

bool light_component::load_content() { return true; }

void light_component::update(float delta_time)
{
	// update light data
	_light->_position = _position;
	_light->_direction = _direction;
}

void light_component::render()
{ 

}

// Rotates the directional light using Euler angles
void light_component::rotate(const glm::vec3 &rotation)
{
	// Convert Euler angles to a quaternion
	glm::quat q(rotation);
	// Use quaternion based rotate
	rotate(q); 
}

// Rotates the directional light using the quaternion
void light_component::rotate(const glm::quat &rotation)
{
	// Get matrix transform
	auto rot = glm::mat3_cast(rotation);
	// Transform the current direction
	_direction = rot * _direction;
}

void light_component::unload_content() {}
void light_component::shutdown() {}