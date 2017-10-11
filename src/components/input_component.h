//
// Created by zoe on 10/10/17.
//

#ifndef RACETHEMOON_INPUT_COMPONENT_H
#define RACETHEMOON_INPUT_COMPONENT_H

#endif //RACETHEMOON_INPUT_COMPONENT_H


#include "../component.h"
#include "../entity.h"


struct input_component : public component
{
private:
    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;
public:
    input_component(std::shared_ptr<entity> &e);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};