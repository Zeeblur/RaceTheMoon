#include "collider_component.h"

collider_component::collider_component(std::shared_ptr<entity> &e, collider_data &data)
	: _parent(e), _data(data)
{
	_visible = false;
	_data.active = true;
}

bool collider_component::initialise()
{
	return true;
}

bool collider_component::load_content()
{
	return true;
}

void collider_component::update(float delta_time)
{

	// If collider object is active
	if (_data.active)
	{

		// Update center point for collisions
		_data.collider.centerPoint.x = _parent->get_trans().x;
		_data.collider.centerPoint.y = _parent->get_trans().y;
		_data.collider.centerPoint.z = _parent->get_trans().z;

		// Update radius based on scale
		//_data.collider.radius[0] = _parent->get_trans().scale.x;
		//_data.collider.radius[1] = _parent->get_trans().scale.y;
		//_data.collider.radius[2] = _parent->get_trans().scale.z;

		//std::cout << _parent->get_name() << ", pos, x: " << _parent->get_trans().x << ", y: " << _parent->get_trans().y << ", z: " << _parent->get_trans().z << std::endl;

		//std::cout << _parent->get_name() << ", scale, x: " << _parent->get_trans().scale.x << ", y: " << _parent->get_trans().scale.y << ", z: " << _parent->get_trans().scale.z << std::endl;

		//std::cout << "center point is x: " << _data.collider.centerPoint.x << ", y: " << _data.collider.centerPoint.y << ", z: " << _data.collider.centerPoint.z << std::endl;
		//std::cout << "radius dx is: " << _data.collider.radius[0] << ", dy: " << _data.collider.radius[1] << ", dz: " << _data.collider.radius[2] << std::endl;
	}

}

void collider_component::render()
{
}

void collider_component::unload_content()
{
}

void collider_component::shutdown()
{
}