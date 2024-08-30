#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../world/block/meta/Liquid.h"
#include "../math/geometry/Orientation.h"
#include "../math/geometry/Transform.h"
#include "../math/shapes/AABB.h"
#include "../render/model/Model.h"
#include "collider/Collider.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"

class World;

class GameObject {
protected:
	World* world;
public:
	std::unique_ptr<Collider> collider;
	std::shared_ptr<Model> model;
	Orientation orientation;
	Transform transform;
	RigidBody rigidBody;

	GameObject(World* world);
	~GameObject();

	World* const getWorld() { return world; }
	void hookWorld(World* world) { this->world = world; }

	void updateTransform();
	void updateTransform(Transform& transform);
	Liquid* getLiquidAtObject();
};

#endif