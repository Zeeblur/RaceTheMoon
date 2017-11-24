#include "text_system.h"

using namespace glm;

text_system::text_system()
{
	_visible = false;
}

std::shared_ptr<text_component> text_system::build_component(std::shared_ptr<entity> e, std::string text)
{
	auto td = std::make_shared<text_data>(text_data(text));
	td->text = text;
	_data.push_back(td);
	
	return std::make_shared<text_component>(e, td);
}

bool text_system::initialise()
{
	std::cout << "Physics system initialising" << std::endl;
	return true;
}

bool text_system::load_content()
{
	std::cout << "Physics system loading content" << std::endl;
	return true;
}

void text_system::update(float delta_time)
{
	//std::cout << "Physics system updating" << std::endl;
	for (auto &d : _data)
	{

	}
}

void text_system::render()
{
	// This should never be called.
	std::cout << "Physics system rendering" << std::endl;
}

void text_system::unload_content()
{
	std::cout << "Physics system unloading content" << std::endl;
}

void text_system::shutdown()
{
	std::cout << "Physics system shutting down" << std::endl;
}
