#include "GameObject.h"

#include "../world/World.h"

GameObject::GameObject(World* world)
	: world(world) {

}

GameObject::~GameObject() {
	PhysicsEngine::removeObject(*this);
}

Liquid* GameObject::getLiquidAtObject() {
	std::shared_ptr<Block> block = world->getBlock(transform.position + glm::vec3(0, 0.3f, 0));

	if (block != nullptr)
		return ((Liquid*)block->getType().meta.get());

	return nullptr;
}

void GameObject::applyTransform(Transform& transform) {
	collider->applyTransform(transform);
	model->aabb.applyTransform(transform);
}

void GameObject::applyTransform() {
	collider->applyTransform(transform);
	model->aabb.applyTransform(transform);
}