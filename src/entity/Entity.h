#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "EntitiesDatabase.h"

class World;
class Block;

class Entity : public GameObject {
	void initialize();
public:
	const EntityType* type;

	Entity(EntityID id, World* world = nullptr);

	bool isOnGround() const;
	Block* getTargetBlock() const;
	Liquid* getLiquidAtEyes() const;
};

#endif