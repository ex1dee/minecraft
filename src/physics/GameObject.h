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
	Orientation orientation;
	Transform transform;
	RigidBody rigidBody;
	Collider* collider;
	Model* model;

	GameObject(World* world);
	~GameObject();

	void hookWorld(World* world) { this->world = world; }
	World* const getWorld() { return world; }

	Liquid* getLiquidAtObject();
	void applyTransform();
	void applyTransform(Transform& transform);
};

#endif