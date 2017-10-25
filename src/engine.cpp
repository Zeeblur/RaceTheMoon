#include "engine.h"

#include <iostream>

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
    glfw::runWindow();
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

    while (_running && glfwWindowShouldClose(window) == 0)
    {
        //std::cout << "Engine Running" << std::endl;

        // Update the subsystems.  At the moment use dummy time of 1.0s.  You
        // will want to use a proper timer.
        for (auto &sys : _subsystems)
            if (sys.second->get_active())
                sys.second->update(1.0);
        // Render the subsystems.
        for (auto &sys : _subsystems)
            if (sys.second->get_visible())
                sys.second->render();

    }
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

    // Engine will now exit.
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}




