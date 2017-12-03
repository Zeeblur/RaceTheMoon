#ifndef RACETHEMOON_AUDIO_COMPONENT_H
#define RACETHEMOON_AUDIO_COMPONENT_H
#include <iostream>
#include <vector>
#include <string>
#include "../subsystem.h"
#include <SFML/Audio.hpp>
#include <map>
#include <list>
enum sound_id
{
	button_press
};

enum music_id
{
	menu,
	game
};

class audio_system : public subsystem
{
private:
	std::map<sound_id, std::shared_ptr<sf::SoundBuffer>> buffers;
	std::list<sf::Sound> sounds;
	sf::Music music;
	float volume = 0.0f;
public:
	
	audio_system();

	static inline std::shared_ptr<audio_system> get()
	{
		static std::shared_ptr<audio_system> instance = std::shared_ptr<audio_system>(new audio_system());
		return instance;
	}
	void load_sound(sound_id id, std::string path);

	void play_sound(sound_id id);

	void play_music(music_id id);

	void stop_music();

	void set_volume(float volume);

	void set_paused(bool paused);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};
#endif // RACETHEMOON_AUDIO_COMPONENT_H