#include "Entity.h"

#include "../physics/collider/BoxCollider.h"
#include "../world/RayTracing.h"

Entity::Entity(EntityID id, World* world)
	: GameObject(world) {
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

	PhysicsEngine::addObject(this);
}

bool Entity::isOnGround() {
	glm::vec3 extents = ((BoxCollider*) collider)->getExtents();
	glm::vec3 colliderCenter = transform.position + collider->getPosition();

	return world->getBlock(colliderCenter - glm::vec3(extents.x,  0.00001f, extents.z))->isCollidable()
		|| world->getBlock(colliderCenter - glm::vec3(extents.x,  0.00001f, -extents.z))->isCollidable()
		|| world->getBlock(colliderCenter - glm::vec3(-extents.x, 0.00001f, -extents.z))->isCollidable()
		|| world->getBlock(colliderCenter - glm::vec3(-extents.x, 0.00001f, extents.z))->isCollidable();
}

Block* Entity::getTargetBlock() {
	Ray ray(transform.position + type->eyesOffset, orientation.front);
	
	return RayTracing::getNearestBlock(world, ray, ENTITY_MAX_TARGET_BLOCK_DIST);
}