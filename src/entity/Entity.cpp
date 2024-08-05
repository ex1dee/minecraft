#include "Entity.h"

#include "../physics/collider/BoxCollider.h"
#include "../world/RayTracing.h"

Entity::Entity(EntityID id, World* world)
	: GameObject(world, false) {
	type = EntitiesDatabase::get(id);
	GameObject::world = world;

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

Block* Entity::getTargetBlock() {
	Ray ray(transform.position + type->eyesOffset, orientation.front);
	
	return RayTracing::getNearestBlock(world, ray, ENTITY_MAX_TARGET_BLOCK_DIST);
}