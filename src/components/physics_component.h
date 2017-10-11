//
// Created by zoe on 10/10/17.
//

#include "../component.h"

#ifndef RACETHEMOON_PHYSICS_COMPONENT_H
#define RACETHEMOON_PHYSICS_COMPONENT_H

#endif //RACETHEMOON_PHYSICS_COMPONENT_H


struct physics_data
{
    bool active = false;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct physics_component : public component
{
private:
    // We'll just keep a reference here.  The physics system
    // will maintain the actual data.
    physics_data &_data;

    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;
public:
    physics_component(std::shared_ptr<entity> &e, physics_data &data)
            : _parent(e), _data(data)
    {
        _visible = false;
        _data.active = true;
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
        // We will just update the entity position.
        _parent->get_trans().x = _data.x;
        _parent->get_trans().y = _data.y;
        _parent->get_trans().z = _data.z;
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