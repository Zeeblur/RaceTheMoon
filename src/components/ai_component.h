//
// Created by beej on 08/11/17.
//

#ifndef RACETHEMOON_AI_COMPONENT_H
#define RACETHEMOON_AI_COMPONENT_H

#include "component.h"
#include "../entity.h"

class input_handler;

struct ai_component : public component
{
private:
    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;

    // reference to input handler system
    std::shared_ptr<input_handler> _handler;

public:
    ai_component(std::shared_ptr<entity> &e);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};


#endif //RACETHEMOON_AI_COMPONENT_H

