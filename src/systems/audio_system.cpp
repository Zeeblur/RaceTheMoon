#include "audio_system.h"
#define TINYSOUND_IMPLEMENTATION
#include "../tinysound.h"
#include <stdio.h>


audio_system::audio_system()
{
	_visible = false;
}

bool audio_system::initialise()
{
	std::cout << "Audio system initialising" << std::endl;
	//HWND hwnd = GetConsoleWindow();
	//ctx = tsMakeContext(hwnd, 44000, 15, 0, 1000);
	return true;
}

bool audio_system::load_content()
{
	std::cout << "Audio system loading content" << std::endl;
	return true;
}

void audio_system::update(float delta_time)
{
	static float total_time;
	total_time += delta_time;

	//if (ready_to_mix)
	//tsLock(ctx);


	//tsMix(ctx);

	//std::cout << "Audio system updating" << std::endl;
}

void audio_system::play_one_shot(std::string path, int duration)
{
	//HWND hwnd = GetConsoleWindow();
	//ctx = tsMakeContext(hwnd, 44000, 15, duration, 1);

	//tsLoadedSound loaded = tsLoadWAV(path.c_str());
	//tsPlaySoundDef def = tsMakeDef(&loaded);
	//tsPlayingSound* sound = tsPlaySound(ctx, def);

	//ready_to_mix = true;
	//tsMix(ctx);


	//tsThreadSleepDelay(ctx, 10);

	//tsLoadedSound loaded = tsLoadWAV(path.c_str());
	//tsPlayingSound sound = tsMakePlayingSound(&loaded);
	//tsSpawnMixThread(ctx);
	//tsSleep(500);
	//tsInsertSound(ctx, &sound);
	//tsInsertSound(ctx, &sound);
	//tsPlaySoundDef def = tsMakeDef(&loaded);
	//tsPlaySound(ctx, def);
	//tsMix(ctx);
	//tsSleep(duration * 1000);
	//tsShutdownContext(ctx);
	//tsStopSound(&sound);
	//tsStopAllSounds(ctx);

	//tsFreeSound(&loaded);
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
