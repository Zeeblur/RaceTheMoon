#include "audio_system.h"

using namespace glm;

audio_system::audio_system()
{
	_visible = false;
}

bool audio_system::initialise()
{
	std::cout << "Audio system initialising" << std::endl;
	return true;
}

bool audio_system::load_content()
{
	std::cout << "Audio system loading content" << std::endl;
	return true;
}

void audio_system::update(float delta_time)
{
	//std::cout << "Audio system updating" << std::endl;
}

void audio_system::render()
{
	// This should never be called.
	std::cout << "Audio system rendering" << std::endl;
}

void audio_system::unload_content()
{
	std::cout << "Audio system unloading content" << std::endl;
}

void audio_system::shutdown()
{
	std::cout << "Audio system shutting down" << std::endl;
}
