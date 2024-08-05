#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "EntitiesDatabase.h"

#define ENTITY_MAX_TARGET_BLOCK_DIST 5.0f

class World;
class Block;

class Entity : public GameObject {
	EntityType* type;

	void initialize();
public:
	Entity(EntityID id, World* world = nullptr);

	EntityType* const getType() { return type; }

	Block* getTargetBlock();
};

#endif