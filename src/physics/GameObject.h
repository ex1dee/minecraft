#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../render/model/Model.h"
#include "../math/geometry/Orientation.h"
#include "../math/geometry/Transform.h"
#include "../math/shapes/AABB.h"
#include "collider/Collider.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"

class GameObject {
public:
	Orientation orientation;
	Transform transform;
	RigidBody rigidBody;
	Collider* collider;
	Model* model;

	GameObject(bool updateEveryTick)
		: rigidBody(updateEveryTick) {

	}

	void applyTransform(Transform& transform) {
		collider->applyTransform(transform);
		model->aabb.applyTransform(transform);
	}

	void applyTransform() {
		collider->applyTransform(transform);
		model->aabb.applyTransform(transform);
	}

	~GameObject() {
		delete collider;
	}
};

#endif