#include "Entity.h"

Entity::Entity(EntityID id)
	: GameObject(false) {
	type = EntitiesDatabase::get(id);

	initialize();
}

void Entity::initialize() {
	Transform transform;
	transform.position = type->colliderPosition;

	collider = new BoxCollider(type->colliderExtents, transform);

	model = type->model;
	model->aabb.extents = type->colliderExtents;

	rigidBody.physics = type->physics;
	rigidBody.mass = type->mass;

	if (type->gravity)
		rigidBody.addGravity();

	PhysicsEngine::addObject(this);
}