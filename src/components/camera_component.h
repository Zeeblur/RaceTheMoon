//
// Created by zoe on 18/10/17.
//

#ifndef RACETHEMOON_CAMERA_COMPONENT_H
#define RACETHEMOON_CAMERA_COMPONENT_H

#include "component.h"
#include "../entity.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

enum camera_type
{
	CHASE,
	ORTHO,
};

struct camera_projection
{
	float fov;
	float aspect;
	float near;
	float far;

	camera_type type;
	glm::mat4 model_view;
};

class camera_component : public component
{

private:
	// ptr to perspective data
	camera_projection &_data;

	std::shared_ptr<entity> _parent;

	glm::vec3 _position = glm::vec3(100.f, 100.f, 100.f);
	glm::vec3 _target = glm::vec3(0.f, 0.f, 0.0f);
	glm::vec3 _up = glm::vec3(0.f, 1.f, 0.f);

	// current built view and projection matrices
	glm::mat4 _view;
	glm::mat4 _projection;

	// may split this into extra class - chasecamera stuff


	// The offset of the camera from its desired position
	glm::vec3 _pos_offset = glm::vec3(100.f);

	// The offset of the camera relative to the target
	glm::vec3 _target_offset;

	// Springiness factor of the camera
	float _springiness = 5.0f;

	
public:
	camera_component(std::shared_ptr<entity> &e, camera_projection &data);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;

	void set_projection(camera_projection &data);

	// Moves the camera
	void move(const glm::vec3 &translation);

	glm::mat4 get_projection() const { return _projection; }
	glm::mat4 get_view() const { return _view; }
};


#endif //RACETHEMOON_CAMERA_COMPONENT_H

