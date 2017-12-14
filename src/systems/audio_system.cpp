#include "audio_system.h"
#include <stdio.h>
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
	load_sound(button_press, "res/sounds/click.wav");
	return true;
}

void audio_system::update(float delta_time)
{
	// Will remove sounds that have stopped playing
	sounds.remove_if([](const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void audio_system::load_sound(sound_id id, std::string path)
{
	// Load a sound buffer from a wav file
	std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
	if (!buffer.get()->loadFromFile(path))
		return;

	// Display sound informations
	std::cout << path << std::endl;
	std::cout << " " << buffer.get()->getDuration().asSeconds() << " seconds" << std::endl;
	std::cout << " " << buffer.get()->getSampleRate() << " samples / sec" << std::endl;
	std::cout << " " << buffer.get()->getChannelCount() << " channels" << std::endl;

	buffers.insert(std::pair<sound_id, std::shared_ptr<sf::SoundBuffer>>(id, buffer));
}

void audio_system::play_sound(sound_id id)
{
	std::shared_ptr<sf::SoundBuffer> sb_ptr = buffers.find(id)->second;
	sf::SoundBuffer* sb = sb_ptr.get();
	sounds.push_back(sf::Sound(*sb));
	sf::Sound& sound = sounds.back();

	sound.play();
}


void audio_system::play_music(music_id id)
{
	std::string filename = "res/sounds/menu.wav";
	switch (id)
	{
		case game:
			filename = "res/sounds/game.wav";
			break;
		case menu:
			filename = "res/sounds/menu.wav";
			break;
	}
	
	
	if (!music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");
	
	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void audio_system::stop_music()
{
	music.stop();
}

void audio_system::set_volume(float volume)
{
	this->volume = 0;// volume;
}

void audio_system::set_paused(bool paused)
{
	if (paused)
		music.pause();
	else
		music.play();
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
