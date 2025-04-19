#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../world/block/meta/Liquid.h"
#include "../math/geometry/Orientation.h"
#include "../math/geometry/Transform.h"
#include "../math/shapes/AABB.h"
#include "../render/model/Model.h"
#include "../utils/UUIDWrapper.h"
#include "collider/Collider.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"

constexpr float GROUND_OFFSET_Y = -0.00001f;

class World;
class Block;

class GameObject {
protected:
	bool collidesWithObjects;
	std::shared_ptr<Model> model;
	UUIDWrapper uuid;
	World* world;
public:
	std::unique_ptr<Collider> collider;
	Orientation orientation;
	Transform transform;
	RigidBody rigidBody;

	GameObject();
	~GameObject();

	bool operator==(const GameObject& other) const { return uuid == other.uuid; }
	bool operator!=(const GameObject& other) const { return !operator==(other); }

	World* const getWorld() const { return world; }
	const UUIDWrapper& getUUID() const { return uuid; }
	const std::shared_ptr<Model>& getModel() const { return model; }
	bool isCollidesWithObjects() const { return collidesWithObjects; }
	void hookWorld(World* const world) { this->world = world; }

	bool isAtLoadedChunk() const;
	bool isAtBufferedChunk() const;
	void applyTransform();
	void applyTransform(Transform& transform);
	std::shared_ptr<Block> getGround() const;
	Liquid* getLiquidAtObject() const;
};

#endif