//
// Created by zoe on 18/10/17.
//
#define GLM_ENABLE_EXPERIMENTAL
#include "camera_component.h"

camera_component::camera_component(std::shared_ptr<entity> &e, std::shared_ptr<camera_projection> data)
	: _parent(e), _data(data)
{}

bool camera_component::initialise()
{ 
	// initialise the camera.

	// set perspective.
	set_projection_view(_data);

	return true;
}

bool camera_component::load_content() { return true; }
void camera_component::render() {} // should never be called
void camera_component::unload_content() {}
void camera_component::shutdown() {}

void camera_component::set_projection_view(std::shared_ptr<camera_projection> data)
{
	int width = 0, height = 0;
	glfwGetWindowSize(glfw::window, &width, &height);
	_data = data;
	switch(data->type)
	{
	case CHASE:
		// create proj matrix
		_projection = glm::perspective(_data->fov, _data->aspect, _data->near, _data->far);
		// set view
		_view = glm::lookAt(_position, _target, _up);
		break;
	case ORTHO:
		_projection = glm::ortho(_data->left, _data->left*-1.0f, _data->bottom, _data->bottom * -1.0f, _data->near, _data->far);		
		_data->model_view = _projection;
		break;
	}

}

void camera_component::update(float delta_time)
{
	// update chase 
	if (_data->type == ORTHO)
		return;

	glm::vec3 target_pos = glm::vec3(_parent->get_trans().x, _parent->get_trans().y, _parent->get_trans().z);

	glm::quat target_rot = _parent->get_trans().rotation;

	glm::quat _relative_rotation = glm::quat();

	// Calculate the combined rotation as a quaternion
	glm::quat rotation = target_rot * _relative_rotation;

	// Now calculate the desired position
	glm::vec3 desired_position = target_pos + (rotation * _pos_offset);
	// Our actual position lies somewhere between our current position and the
	// desired position
	// can add this here but not working properly
	//_position = glm::mix(_position, desired_position, _springiness);

	// Calculate new target offset based on rotation
	_target_offset = rotation * _target_offset;
	// Target is then the target position plus this offset
	_target = target_pos +_target_offset;

	// Calculate up vector based on rotation //rotation *
	_up = rotation * glm::vec3(0.0f, 1.0f, 0.0f);

	// Calculate view matrix
	_view = glm::lookAt(desired_position, _target, _up);

	_data->model_view = _projection * _view;
}
