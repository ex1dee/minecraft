#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "EntitiesDatabase.h"

class Entity : public GameObject {
	EntityType* type;
	glm::vec3 position;

	void initialize();
public:
	Entity(EntityID id);

	EntityType* getType() { return type; }
};

#endif