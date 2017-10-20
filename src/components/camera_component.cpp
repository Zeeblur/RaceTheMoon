//
// Created by zoe on 18/10/17.
//


#include "camera_component.h"

camera_component::camera_component(std::shared_ptr<entity> &e, camera_projection &data)
	: _parent(e), _data(data)
{}

bool camera_component::initialise()
{ 
	// initialise the camera.

	// set perspective.
	set_projection(_data);

	// set view
	_view = glm::lookAt(_position, _target, _up);

	return true;
}

bool camera_component::load_content() { return true; }
void camera_component::render() {} // should never be called
void camera_component::unload_content() {}
void camera_component::shutdown() {}

void camera_component::set_projection(camera_projection &data)
{

	_data = data;
	
	// create proj matrix
	_projection = glm::perspective(_data.fov, _data.aspect, _data.near, _data.far);
}

void camera_component::update(float delta_time)
{
	// update chase 

	glm::vec3 target_pos = glm::vec3(_parent->get_trans().x, _parent->get_trans().y, _parent->get_trans().z);

	// Calculate the combined rotation as a quaternion
	//glm::quat rotation(_parent->get_trans());// +_relative_rotation);

	// Now calculate the desired position
	glm::vec3 desired_position = target_pos + _pos_offset; // + (rotation * _pos_offset);
	// Our actual position lies somewhere between our current position and the
	// desired position
	_position = glm::mix(_position, desired_position, _springiness);

	// Calculate new target offset based on rotation
	//_target_offset = rotation * _target_offset;
	// Target is then the target position plus this offset
	_target = target_pos + _target_offset;

	// Calculate up vector based on rotation
	//_up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);

	// Calculate view matrix
	//_view = glm::lookAt(_position, _target, _up);
	_view = glm::lookAt(desired_position, _target, _up);

	_data.model_view = _projection * _view;
}

void camera_component::move(const glm::vec3 &translation)
{
	// Just add translation vector to current translation
	//_translation += translation;
}