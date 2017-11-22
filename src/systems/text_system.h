#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../components/component.h"
#include "../subsystem.h"
#include "../components/text_component.h"
#include "../entity_manager.h"

class text_system : public subsystem
{
private:
	std::vector<std::shared_ptr<text_data>> _data;

	text_system();

public:

	static inline std::shared_ptr<text_system> get()
	{
		static std::shared_ptr<text_system> instance = std::shared_ptr<text_system>(new text_system());
		return instance;
	}

	std::shared_ptr<text_component> build_component(std::shared_ptr<entity> e, std::string text);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};