//
// Created by zoe on 09/11/17.
//

#ifndef RACETHEMOON_SCORE_COMPONENT_H
#define RACETHEMOON_SCORE_COMPONENT_H

#include "component.h"
#include "../entity.h"

struct score_data
{
    int health = 100;
    int score = 0;
    // contain speedup and boosts here too?
};

struct score_component : public component
{
private:
    // We'll just keep a reference here.  The physics system
    // will maintain the actual data.
    std::shared_ptr<score_data> _data;

    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;
public:
    score_component(std::shared_ptr<entity> &e, std::shared_ptr<score_data> &data);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};


#endif //RACETHEMOON_SCORE_COMPONENT_H
