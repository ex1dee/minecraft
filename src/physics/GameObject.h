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

class World;

class GameObject {
protected:
	bool collidesWithObjects;
	UUIDWrapper uuid;
	World* world;
public:
	std::unique_ptr<Collider> collider;
	std::shared_ptr<Model> model;
	Orientation orientation;
	Transform transform;
	RigidBody rigidBody;

	GameObject();
	~GameObject();

	bool operator==(const GameObject& other) const { return uuid == other.uuid; }
	bool operator!=(const GameObject& other) const { return !operator==(other); }

	World* const getWorld() { return world; }
	const UUIDWrapper& getUUID() const { return uuid; }
	bool isCollidesWithObjects() { return collidesWithObjects; }
	void hookWorld(World* const world) { this->world = world; }

	void updateTransform();
	void updateTransform(Transform& transform);
	Liquid* getLiquidAtObject();
};

#endif