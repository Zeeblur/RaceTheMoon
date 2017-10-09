#pragma once
#include "entity.h"
#include "component.h"
class clickable_component : component
{
	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};