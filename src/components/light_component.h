//
// Created by zoe on 24/10/17.
//

#ifndef RACETHEMOON_LIGHT_COMPONENT_H
#define RACETHEMOON_LIGHT_COMPONENT_H

#include "component.h"
#include "../entity.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../glfw.h"
#include "../opengl_util.h"

class light_component : public component
{

private:
	std::shared_ptr<entity> _parent;

	std::shared_ptr<gl::light_data> _light;

	glm::vec3 _position;
	glm::vec3 _direction;

public:
	light_component(std::shared_ptr<entity> &e, std::shared_ptr<gl::light_data> &data);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;

	void rotate(const glm::vec3 &rotation);

	void rotate(const glm::quat &rotation);
};


#endif //RACETHEMOON_LIGHT_COMPONENT_H

