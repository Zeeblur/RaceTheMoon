#include "engine.h"
#include "thread_pool.h"

#include <iostream>
#include <chrono>
#include <fstream>
#include "settings_state.h"


using namespace glfw;

void engine::add_subsystem(const std::string &name, std::shared_ptr<subsystem> sys)
{
    _subsystems[name] = sys;
}

std::shared_ptr<subsystem> engine::get_subsystem(const std::string &name)
{
    auto found = _subsystems.find(name);
    if (found == _subsystems.end())
        return nullptr;
    return found->second;
}

// Runs the engine.  Note that this technique takes no account of subsystem order.
// If subsystem order is important consider using another mechanism.
void engine::run()
{
    initGraphics();
    initSubsystems();
    mainLoop();
    cleanup();
}

void engine::initWindowMan()
{
	std::ifstream user_pref_file;

	user_pref_file.open("res/buttons.txt");
	if (!user_pref_file)
	{
		// Close file, not found
		user_pref_file.close();
		// File not found, create new one with default settings
		std::ofstream user_pref_file_out("res/buttons.txt");
		if (user_pref_file_out.is_open())
		{
			user_pref_file_out << "Left: " << GLFW_KEY_A << "\n";
			user_pref_file_out << "Right: " << GLFW_KEY_D << "\n";
			user_pref_file_out << "Front: " << GLFW_KEY_W << "\n";
			user_pref_file_out << "Back: " << GLFW_KEY_S << "\n";
			user_pref_file_out << "NavigationUp: " << GLFW_KEY_UP << "\n";
			user_pref_file_out << "NavigationDown: " << GLFW_KEY_DOWN << "\n";
			user_pref_file_out << "NavigationLeft: " << GLFW_KEY_LEFT << "\n";
			user_pref_file_out << "NavigationRight: " << GLFW_KEY_RIGHT << "\n";
			user_pref_file_out << "JoystickEnter: " << 0 << "\n";
			user_pref_file_out << "JoystickUp: " << 10 << "\n";
			user_pref_file_out << "JoystickDown: " << 12 << "\n";
			user_pref_file_out << "JoystickLeft: " << 11 << "\n"; // is this right?
			user_pref_file_out << "JoystickRight: " << 13 << "\n"; // is this right?
			user_pref_file_out << "Resolution: " << "_1920x1080" << "\n";
			user_pref_file_out << "Windowed: " << "TRUE" << "\n";


		}
		// Close file, finished writing
		user_pref_file_out.close();
	}

	std::string resPref;
	std::string windowPref;

	std::string input = "";
	// Load in keys from file
	while (user_pref_file >> input)
	{
		if (input == "Resolution:")
		{
			user_pref_file >> resPref;
		}
		else if (input == "Windowed:")
		{
			user_pref_file >> windowPref;
		}
	}
	user_pref_file.close();

	bool current_window_mode;

	if (windowPref == "TRUE")
		current_window_mode = true;
	else
		current_window_mode = false;

	// set res
	int resX, resY;

	if (resPref == "_1024x768")
	{
		resX = 1024;
		resY = 768;
	}
	else if (resPref == "_1280x720")
	{
		resX = 1280;
		resY = 720;
	}
	else if (resPref == "_1600x1200")
	{
		resX = 1600;
		resY = 1200;
	}
	else if (resPref == "_1920x1080")
	{
		resX = 1920;
		resY = 1080;
	}
	
	glfw::runWindow(resX, resY, current_window_mode);
}

void engine::initGraphics()
{
}

void engine::initSubsystems()
{

    // Initialise all the subsystems
    for (auto &sys : _subsystems)
    {
        // If initialise fails exit run.
        if (!sys.second->initialise())
        {
            return;
        }
    }

    // Load content for all the subsystems
    for (auto &sys : _subsystems)
    {
        // If load_content fails exit run.
        if (!sys.second->load_content())
        {
            return;
        }
    }
}

void engine::mainLoop()
{
    // Loop until not running.
    // Check if the ESC key was pressed or the window was closed

	float dt = 1 / 60.0;

	auto currentTime = std::chrono::system_clock::now();

    while (_running && glfwWindowShouldClose(window) == 0)
    {
        //std::cout << "Engine Running" << std::endl;
		auto newTime = std::chrono::system_clock::now();

		float frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - currentTime).count();
		currentTime = newTime;

		// variable delta time
		float deltaTime = frameTime / 1000.0f; // std::min (dt) ?
		// Update the subsystems. 
		for (auto &sys : _subsystems)
			if (sys.second->get_active())
				sys.second->update(deltaTime);

        while(thread_pool::get()->jd_.jobs_.size() != 0)
        {
            // wait on the threads to finish
        }

        // Render the subsystems.
        for (auto &sys : _subsystems)
            if (sys.second->get_visible())
                sys.second->render();

        while(thread_pool::get()->jd_.jobs_.size() != 0)
        {
            // wait on the threads to finish
        }
    }

	engine::get()->set_running(false);
}

void engine::cleanup()
{
    // Unload the content.
    for (auto &sys : _subsystems)
    {
        sys.second->unload_content();
    }

    // Shutdown subsystems
    for (auto &sys : _subsystems)
    {
        sys.second->shutdown();
    }


    // Clear out all the subsystems causing destructors to call.
    _subsystems.clear();

    thread_pool::get()->shutdown();

    // Engine will now exit.
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}




