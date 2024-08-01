#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../math/Transform.h"
#include "../math/AABB.h"
#include "collider/Collider.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"

class GameObject {
public:
	Transform transform;
	RigidBody rigidBody;
	Collider* collider;
	AABB aabb;

	GameObject(bool physics = false, bool updateEveryTick = true, float mass = 1.0f)
		: rigidBody(physics, updateEveryTick, mass) {

		PhysicsEngine::addObject(this);
	}

	void applyTransform(Transform& transform) {
		collider->applyTransform(transform);
		aabb.min = transform.position;
	}

	~GameObject() {
		delete collider;
	}
};

#endif