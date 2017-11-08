#include "component.h"
#include "../entity.h"
#include "glm/glm.hpp"

#ifndef RACETHEMOON_COLLIDER_COMPONENT_H
#define RACETHEMOON_COLLIDER_COMPONENT_H

struct AABB
{
	glm::dvec3 centerPoint; // Center point of AABB
	double radius[3]; // Radius - Halfwidth extents (dx, dy, dz)
};

//struct SphereCollider
//{
//	double radius;
//};

struct collider_data
{
	bool active = false;
	std::shared_ptr<AABB> collider;
	collider_data(transform_data trans);
};

struct collider_component : public component
{
private:
	// We'll just keep a reference here.  The physics system
	// will maintain the actual data.
	std::shared_ptr<collider_data> _data;

	// We'll also keep a reference to the parent entity
	std::shared_ptr<entity> _parent;
public:
	collider_component(std::shared_ptr<entity> &e, std::shared_ptr<collider_data> &data);

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

	void unload_content() override final;

	void shutdown() override final;
};

#endif //RACETHEMOON_COLLIDER_COMPONENT_H