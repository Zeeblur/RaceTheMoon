#ifndef RACETHEMOON_AUDIO_COMPONENT_H
#define RACETHEMOON_AUDIO_COMPONENT_H
#include <iostream>
#include <vector>
#include <string>
#include "../subsystem.h"
//#define TINYSOUND_IMPLEMENTATION
#include "../tinysound.h"
class audio_system : public subsystem
{
private:
	tsContext* ctx;
	bool ready_to_mix = false;
public:
	
	audio_system();

	static inline std::shared_ptr<audio_system> get()
	{
		static std::shared_ptr<audio_system> instance = std::shared_ptr<audio_system>(new audio_system());
		return instance;
	}

	void play_one_shot(std::string path, int duration);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};
#endif // RACETHEMOON_AUDIO_COMPONENT_H