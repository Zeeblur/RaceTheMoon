//
// Created by beej on 08/11/17.
//

#ifndef RACETHEMOON_AI_COMPONENT_H
#define RACETHEMOON_AI_COMPONENT_H

#include "component.h"
#include "../entity.h"

class ai_system;

enum ai_type
{
    UPTHENDOWN,
    DOWNTHENUP,
    FORWARDTHENBACK,
    BACKTHENFORWARD,
    RIGHTTHENLEFT,
    LEFTTHENRIGHT,
    SUN_MOON
};

struct ai_data
{
    unsigned int ai_type;
    float min = 0.0f;
    float max = 0.0f;
    glm::vec3 init_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cur_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    bool flagA = 0;
    // current pos
};

struct ai_component : public component
{
private:
    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;

    // reference to ai_system
    std::shared_ptr<ai_system> _ai_system;

    // We'll just keep a reference here.  The ai_system
    // will maintain the actual data.
    std::shared_ptr<ai_data> _ai_data;

    // ai movement commands
//    Command* aiUp_;

public:
    ai_component(std::shared_ptr<entity> &e, std::shared_ptr<ai_data> &ai_data);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;
};


#endif //RACETHEMOON_AI_COMPONENT_H

