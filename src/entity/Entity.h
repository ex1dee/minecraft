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

	std::map<std::string, Animator> animators;
public:
	Transform modelTransform;
	bool isInCameraSpace;

	Entity(EntityID id);
	virtual ~Entity() = default;

	virtual void update(const std::shared_ptr<Player>& player, float deltaTime) {}
	virtual void playIdleAnimation(const std::shared_ptr<Player>& player, float deltaTime) {}

	const EntityType& getType() const { return EntitiesDatabase::get(id); }
	Animator* getAnimator(const std::string& name) { return animators.contains(name) ? &animators[name] : nullptr; }
	bool hasAnimators() const { return !animators.empty(); }

	Ray getViewDirection() const;
	Liquid* getLiquidAtEyes() const;
	glm::vec3 getEyesPosition() const;
	glm::vec3 getColliderCenter() const;
	std::vector<glm::mat4> updateAnimators();
	std::shared_ptr<Block> getTargetBlock() const;
	void setModel(const std::shared_ptr<Model>& model);
	bool isAtBlock(const glm::vec3& position) const;
	bool isAtBlock(const glm::vec3& position, const BlockType& type) const;
	bool isCollidesWithBlock(const glm::vec3& position, const BlockType& type) const;
	bool needUpdate() const;
	bool isOnGround() const;
};

#endif