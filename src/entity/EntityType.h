#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include "../render/model/Model.h"
#include "EntityID.h"

class EntityType {
public:
	EntityID id;
	std::shared_ptr<Model> model;
	glm::vec3 colliderPosition;
	glm::vec3 colliderExtents;
	glm::vec3 eyesOffset;
	float mass;
	bool physics;
	bool gravity;
	Transform offset;
};

#endif