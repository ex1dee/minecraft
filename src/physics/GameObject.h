#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../render/model/Model.h"
#include "../math/geometry/Orientation.h"
#include "../math/geometry/Transform.h"
#include "../math/shapes/AABB.h"
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

	GameObject(World* world)
		: world(world) {

	}

	void applyTransform(Transform& transform) {
		collider->applyTransform(transform);
		model->aabb.applyTransform(transform);
	}

	void applyTransform() {
		collider->applyTransform(transform);
		model->aabb.applyTransform(transform);
	}

	void hookWorld(World* world) { this->world = world; }
	World* const getWorld() { return world; }

	~GameObject() {
		delete collider;
	}
};

#endif