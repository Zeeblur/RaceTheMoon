#pragma once

#include <unordered_map>
#include "entity.h"
#include "component.h"
#include "engine.h"
#include "subsystem.h"
#include "engine_state.h"

class entity_state
{
public:
    virtual ~entity_state() = default;

    virtual void on_enter(std::shared_ptr<entity> e) = 0;

    virtual void on_update(std::shared_ptr<entity> e, float delta_time) = 0;

    virtual void on_exit(std::shared_ptr<entity> e) = 0;
};

class entity_state_machine : public component
{
private:
    std::unordered_map<std::string, std::shared_ptr<entity_state>> _states;

    std::string _current_state_name = "";

    std::shared_ptr<entity_state> _current_state = nullptr;

    std::shared_ptr<entity> _owner = nullptr;

public:
    entity_state_machine(std::shared_ptr<entity> owner)
        : _owner(owner)
    {
        _visible = false;
    }

    void add_state(const std::string &name, std::shared_ptr<entity_state> state)
    {
        _states[name] = state;
    }

    void change_state(const std::string &name)
    {
        if (name != _current_state_name)
        {
            auto found = _states.find(name);
            if (found != _states.end())
            {
                if (_current_state != nullptr)
                    _current_state->on_exit(_owner);
                _current_state = found->second;
                _current_state->on_enter(_owner);
                _current_state_name = name;
            }
            else
            {
                throw std::invalid_argument("state not found");
            }
        }
    }

    bool initialise() override final
    {
        return true;
    }

    bool load_content() override final
    {
        return true;
    }

    void update(float delta_time) override final
    {
        if (_current_state != nullptr)
            _current_state->on_update(_owner, delta_time);
    }

    void render() override final
    {

    }

    void unload_content() override final
    {

    }

    void shutdown() override final
    {

    }
};