#pragma once

#include <memory>

// Represents a subsystem of the engine.  For example, physics, rendering, AI.
// What you define as a system is your choice.
class subsystem
{
protected:
    // Flag to indicate that the system is currently active and should be updated
    // each frame.
    bool _active = true;

    // Flag to indicate that the system has rendererable components and should have
    // its components rendered per frame.
    bool _visible = true;

public:
    // Default constructor.
    subsystem() = default;

    // Define default copy constructor
    subsystem(const subsystem &other) = default;

    // Define default move constructor
    subsystem(subsystem &&rhs) = default;

    // Define default copy assignment operator.
    subsystem& operator=(const subsystem &other) = default;

    // Define default move assignment operator.
    subsystem& operator=(subsystem &&rhs) = default;

    // Destructor.
    virtual ~subsystem() = default;

    // Gets the current active status.
    // Note a getter is const (does not change the object) and does not throw an exception
    // noexcept
    bool get_active() const noexcept { return _active; }

    // Gets the current visible status.
    // Note a getter is const (does not change the object) and does not throw an exception
    // noexcept
    bool get_visible() const noexcept { return _visible; }

    // Sets the value of active.
    // Note the setter does not throw an exception - noexcept.
    void set_active(bool active) noexcept { _active = active; }

    // Sets the value of visible.
    // Note the setter does not throw an exception - noexcept.
    void set_visible(bool visible) noexcept { _visible = visible; }

    // This is the publically visible initialise method
    virtual bool initialise() = 0;

    // This is the publically visible load_content method.
    virtual bool load_content() = 0;

    // This is the publically visible update method.
    virtual void update(float delta_time) = 0;

    // This is the publically visible render method.
    virtual void render() = 0;

    // This is the publically visible unload_content method.
    virtual void unload_content() = 0;

    // This is the publically visible shutdown method.
    virtual void shutdown() = 0;

    virtual void reset(){};

    virtual void hurt(){};

    virtual void addPointsPowerUp(){};
};