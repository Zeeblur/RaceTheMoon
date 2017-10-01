#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "subsystem.h"
#include "glfw.h"


// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

class engine
{
private:
    // Flag to indicate if the engine is running or not.
    bool _running = true;

    // The collection of subsystems.  Note we are maintaining pointers here.
    std::unordered_map<std::string, std::shared_ptr<subsystem>> _subsystems;

    engine() = default;
public:

    inline static std::shared_ptr<engine> get()
    {
        static std::shared_ptr<engine> instance(new engine());
        return instance;
    }

    // Get the current running value.
    bool get_running() const noexcept { return _running; }

    // Set the current running value.
    void set_running(bool value) noexcept { _running = value; }

    void add_subsystem(const std::string &name, std::shared_ptr<subsystem> sys)
    {
        _subsystems[name] = sys;
    }

    std::shared_ptr<subsystem> get_subsystem(const std::string &name)
    {
        auto found = _subsystems.find(name);
        if (found == _subsystems.end())
            return nullptr;
        return found->second;
    }

    // Runs the engine.  Note that this technique takes no account of subsystem order.
    // If subsystem order is important consider using another mechanism.
    void run()
    {

        glfw::run();

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


        // Loop until not running.
        // Check if the ESC key was pressed or the window was closed
        while (_running && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 )
        {
            std::cout << "Engine Running" << std::endl;

            // Update the subsystems.  At the moment use dummy time of 1.0s.  You
            // will want to use a proper timer.
            for (auto &sys : _subsystems)
                if (sys.second->get_active())
                    sys.second->update(1.0);
            // Render the subsystems.
            for (auto &sys : _subsystems)
                if (sys.second->get_visible())
                    sys.second->render();


                //Draw things.



        }

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
};