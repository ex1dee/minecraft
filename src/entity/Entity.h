#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "EntitiesDatabase.h"

#define ENTITY_MAX_TARGET_BLOCK_DIST 5.0f

class World;
class Block;

class Entity : public GameObject {
	void initialize();
protected:
	EntityType* type;
public:
	Entity(EntityID id, World* world = nullptr);

	EntityType* const getType() { return type; }

	bool isOnGround();
	Block* getTargetBlock();
};

#endif