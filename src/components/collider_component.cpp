#include "collider_component.h"

collider_data::collider_data(transform_data trans, int behaviour, std::string name)
{

    behaviour_ = (colType)behaviour;

	switch (trans.colType) {
        case 0:
        {

            sphere* c = new sphere();
            c->radius = glm::max(glm::length(trans.max), glm::length(trans.min));
            auto maxScale = glm::max(trans.scale.x, trans.scale.y);
            maxScale = glm::max(maxScale, trans.scale.z);
            c->radius *= maxScale;

			this->collider.reset(c);

        }
			break;
		case 1:
        {
            AABB* cl = new AABB();
            // dx
            auto difference = glm::abs(trans.max) + glm::abs(trans.min);
            difference /= 2.0f;
            cl->radius[0] = difference.x * trans.scale.x;
            cl->radius[1] = difference.y * trans.scale.y;
            cl->radius[2] = difference.z * trans.scale.z;

			this->collider.reset(cl);


        }
			break;
	}


	this->collider->centerPoint.x = trans.x;
	this->collider->centerPoint.y = trans.y;
	this->collider->centerPoint.z = trans.z;

    name_ = name;


	//this->collider = std::move(col);
}

collider_component::collider_component(std::shared_ptr<entity> &e, std::shared_ptr<collider_data> data)
	: _parent(e), _data(data)
{
	_visible = false;
	_data->active = true;
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
	if (_data->active)
	{
		// Update center point for collisions
		_data->collider->centerPoint.x = _parent->get_trans().x;
		_data->collider->centerPoint.y = _parent->get_trans().y;
		_data->collider->centerPoint.z = _parent->get_trans().z;

//		std::cout << _parent->get_name() << ", pos, x: " << _parent->get_trans().x << ", y: " << _parent->get_trans().y << ", z: " << _parent->get_trans().z << std::endl;
//
//		std::cout << _parent->get_name() << ", scale, x: " << _parent->get_trans().scale.x << ", y: " << _parent->get_trans().scale.y << ", z: " << _parent->get_trans().scale.z << std::endl;
//
//		std::cout << "center point is x: " << _data->collider->centerPoint.x << ", y: " << _data->collider->centerPoint.y << ", z: " << _data->collider->centerPoint.z << std::endl;
//		//std::cout << "radius dx is: " << _data->collider->radius[0] << ", dy: " << _data->collider->radius[1] << ", dz: " << _data->collider->radius[2] << std::endl;

	}

}

void collider_component::render()
{
}

void collider_component::unload_content()
{
	_data.reset();
}

void collider_component::shutdown()
{
}