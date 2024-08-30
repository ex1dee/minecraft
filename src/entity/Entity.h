#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "../world/block/Block.h"
#include "../math/shapes/Ray.h"
#include "EntitiesDatabase.h"

class World;
class Block;

class Entity : public GameObject {
	EntityID id;
public:
	Entity(EntityID id, World* world = nullptr);
	virtual ~Entity() = default;

	const EntityType& getType() const { return EntitiesDatabase::get(id); }

	Ray getDirection() const;
	Liquid* getLiquidAtEyes() const;
	std::shared_ptr<Block> getTargetBlock() const;

	bool isAtBlock(const glm::vec3& position, const BlockType& type) const;
	bool isOnGround() const;
};

#endif