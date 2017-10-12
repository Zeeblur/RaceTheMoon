//
// Created by zoe on 10/10/17.
//

#ifndef RACETHEMOON_INPUT_COMPONENT_H
#define RACETHEMOON_INPUT_COMPONENT_H

#include "../component.h"
#include "../entity.h"

class input_handler;

struct input_component : public component
{
private:
    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;

    // reference to input handler system
    std::shared_ptr<input_handler> _handler;

public:
    input_component(std::shared_ptr<entity> &e);// std::shared_ptr<input_handler> &ih);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};


#endif //RACETHEMOON_INPUT_COMPONENT_H

