#include "GameObject.h"

#include "../world/World.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {
	PhysicsEngine::removeObject(*this);
}

bool GameObject::isAtLoadedChunk() const {
	std::shared_ptr<Chunk> chunk = world->getChunk(transform.position);

	return chunk != nullptr && chunk->isLoaded();
}

bool GameObject::isAtBufferedChunk() const {
	std::shared_ptr<Chunk> chunk = world->getChunk(transform.position);

	return chunk != nullptr && chunk->hasBuffered();
}

Liquid* GameObject::getLiquidAtObject() const {
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

std::shared_ptr<Block> GameObject::getGround() const {
	return world->getBlock(transform.position + glm::vec3(0, GROUND_OFFSET_Y, 0));
}