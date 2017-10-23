#pragma once

#include <memory>

class component
{
protected:
    bool _active = true;
    bool _visible = true;

public:
    component() = default;

    virtual ~component() = default;

    void set_active(bool value) noexcept { _active = value; }
    void set_visible(bool value) noexcept { _visible = value; }
    bool get_active() const noexcept { return _active; }
    bool get_visible() const noexcept { return _visible; }

    virtual bool initialise() = 0;

    virtual bool load_content() = 0;

    virtual void update(float delta_time) = 0;

    virtual void render() = 0;

    virtual void unload_content() = 0;

    virtual void shutdown() = 0;
};