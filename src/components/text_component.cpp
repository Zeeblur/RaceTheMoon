#include "text_component.h"

text_data::text_data(std::string text)
{
	this->text = text;
}

text_component::text_component(std::shared_ptr<entity> &e, std::shared_ptr<text_data> &data)
	: _parent(e), _data(data)
{
	_visible = false;
	_data->active = true;
}

bool text_component::initialise()
{
	return true;
}

bool text_component::load_content()
{
	return true;
}

void text_component::update(float delta_time)
{

}

void text_component::render()
{
}

void text_component::unload_content()
{
}

void text_component::shutdown()
{
}