#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "subsystem.h"
#include "glfw.h"
#include "opengl_util.h"

class engine
{
private:
	// Flag to indicate if the engine is running or not.
	bool _running = true;

	// The collection of subsystems.  Note we are maintaining pointers here.
	std::unordered_map<std::string, std::shared_ptr<subsystem>> _subsystems;

	engine() = default;

	// app stuff
	void initWindowMan();
	void initGraphics();
	void initSubsystems();
	void mainLoop();
	void cleanup();



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

	void add_subsystem(const std::string &name, std::shared_ptr<subsystem> sys);

	std::shared_ptr<subsystem> get_subsystem(const std::string &name);

	// Runs the engine.  Note that this technique takes no account of subsystem order.
	// If subsystem order is important consider using another mechanism.
	void run();

};