#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "EntitiesDatabase.h"

class World;
class Block;

class Entity : public GameObject {
	EntityID id;

	void initialize();
public:
	Entity(EntityID id, World* world = nullptr);

	const EntityType& getType() const { return EntitiesDatabase::get(id); }

	bool isOnGround() const;
	std::shared_ptr<Block> getTargetBlock() const;
	Liquid* getLiquidAtEyes() const;
};

#endif