#pragma once
#include "component.h"
#include "../entity.h"
#include "glm/glm.hpp"

struct text_data
{
	bool active = false;
	std::string text;
	text_data(std::string text);
};

struct text_component : public component
{
private:
	// We'll also keep a reference to the parent entity
	std::shared_ptr<entity> _parent;
public:
	// We'll just keep a reference here.  The text system
	// will maintain the actual data.
	std::shared_ptr<text_data> _data;

	text_component(std::shared_ptr<entity> &e, std::shared_ptr<text_data> &data);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;

};