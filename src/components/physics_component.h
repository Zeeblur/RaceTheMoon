//
// Created by zoe on 10/10/17.
//

#include "component.h"
#include "../entity.h"
#include "glm/glm.hpp"

#ifndef RACETHEMOON_PHYSICS_COMPONENT_H
#define RACETHEMOON_PHYSICS_COMPONENT_H

struct physics_data
{
	transform_data _orig_trans;
    bool active = false;
    std::string name_ = "";
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
	glm::quat rotation = glm::quat();
	glm::quat rotateby = glm::quat();
    glm::vec3 currentVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    bool moveRequest = false;
    physics_data(transform_data trans, std::string name_ = "");
	void reset_data();
};

struct physics_component : public component
{
private:
    // We'll just keep a reference here.  The physics system
    // will maintain the actual data.
    std::shared_ptr<physics_data> _data;

    // We'll also keep a reference to the parent entity
    std::shared_ptr<entity> _parent;

    glm::vec3 acceleration = glm::vec3(2.0f);
public:
    physics_component(std::shared_ptr<entity> &e, std::shared_ptr<physics_data> &data);

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;

    void add_impulse(glm::vec3& direction);

	std::shared_ptr<physics_data> get_data() { return _data; };
};

#endif //RACETHEMOON_PHYSICS_COMPONENT_H