//
// Created by zoe on 10/10/17.
//

#include "physics_component.h"

physics_data::physics_data(transform_data trans, std::string name_) : x(trans.x), y(trans.y), z(trans.z), rotation(trans.rotation), _orig_trans(trans), name_(name_)
{}

void physics_data::reset_data()
{
	x = _orig_trans.x;
	y = _orig_trans.y;
	z = _orig_trans.z;
	rotation = _orig_trans.rotation;
	rotateby = glm::quat();
	currentVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

physics_component::physics_component(std::shared_ptr<entity> &e, std::shared_ptr<physics_data> &data)
    : _parent(e), _data(data)
{
    _visible = false;
    _data->active = true;
}

bool physics_component::initialise()
{
	_data->reset_data();
    return true;
}

bool physics_component::load_content()
{
    return true;
}

void physics_component::update(float delta_time)
{
    // We will just update the entity position.
    _parent->get_trans().x = _data->x;
    _parent->get_trans().y = _data->y;
	_parent->get_trans().z = _data->z;
	_parent->get_trans().rotation = _data->rotation * _data->rotateby;

	turnt = false;
}

void physics_component::render()
{
}

void physics_component::unload_content()
{
	// remove collider data
	_data.reset();
}

void physics_component::shutdown()
{
}

void physics_component::add_impulse(glm::vec3& direction)
{
    _data->moveRequest = true;
	
	if (direction.z == 0)
	{
		auto reverse = glm::vec3(direction.z, direction.y, direction.x);
		_data->rotateby = glm::angleAxis(glm::radians(-20.0f), reverse);
		turnt = true;
	}

	if (!turnt)
	{
		auto reverse = glm::vec3(direction.z, direction.y, direction.x);
		_data->rotateby = glm::angleAxis(glm::radians(-20.0f), reverse);
	}
	

    _data->currentVelocity += (direction * acceleration);
}