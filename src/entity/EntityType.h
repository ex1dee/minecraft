#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include "../utils/PointerUtils.h"
#include "../render/model/Model.h"
#include "EntityID.h"

class EntityType {
public:
	EntityID id;
	float mass;
	bool physics;
	bool gravity;
	Model* model;
	Transform offset;
	glm::vec3 colliderPosition;
	glm::vec3 colliderExtents;
	glm::vec3 eyesOffset;

	~EntityType() {
		freePointer(&model);
	}
};

#endif