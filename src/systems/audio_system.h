#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../entity.h"
#include "../subsystem.h"
#include "../entity_manager.h"

class audio_system : public subsystem
{
private:

public:

	audio_system();

	static inline std::shared_ptr<audio_system> get()
	{
		static std::shared_ptr<audio_system> instance = std::shared_ptr<audio_system>(new audio_system());
		return instance;
	}

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};