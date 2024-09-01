#ifndef ENTITY_H
#define ENTITY_H

#include "../physics/GameObject.h"
#include "../world/block/Block.h"
#include "../utils/UUIDWrapper.h"
#include "../math/shapes/Ray.h"
#include "EntitiesDatabase.h"

class Player;
class World;
class Block;

class Entity : public GameObject {
	EntityID id;
public:
	Transform modelTransform;

	Entity(EntityID id);
	virtual ~Entity() = default;

	virtual void update(const std::shared_ptr<Player>& player, float deltaTime) {}
	virtual void playAnimation(const std::shared_ptr<Player>& player, float deltaTime) {}

	const EntityType& getType() const { return EntitiesDatabase::get(id); }

	Ray getViewDirection() const;
	Liquid* getLiquidAtEyes() const;
	glm::vec3 getEyesPosition() const;
	glm::vec3 getColliderCenter() const;
	std::shared_ptr<Block> getTargetBlock() const;
	bool isAtBlock(const glm::vec3& position) const;
	bool isAtBlock(const glm::vec3& position, const BlockType& type) const;
	bool isCollidesWithBlock(const glm::vec3& position, const BlockType& type) const;
	bool needUpdate() const;
	bool isOnGround() const;
};

#endif