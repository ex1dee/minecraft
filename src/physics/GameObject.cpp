#include "GameObject.h"

#include "../world/World.h"

GameObject::GameObject() {

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

void GameObject::updateTransform(Transform& transform) {
	collider->updateTransform(transform);
	model->aabb.updateTransform(transform);
}

void GameObject::updateTransform() {
	collider->updateTransform(transform);
	model->aabb.updateTransform(transform);
}