#include "GameObject.h"

#include "../world/World.h"

GameObject::GameObject(World* world)
	: world(world) {

}

GameObject::~GameObject() {
	delete collider;
}

Liquid* GameObject::getLiquidAtObject() {
	Block* block = world->getBlock(transform.position);
	Liquid* liquid = block->getMeta<Liquid>();

	if (block != nullptr && liquid != nullptr) {
		return liquid;
	}
}

void GameObject::applyTransform(Transform& transform) {
	collider->applyTransform(transform);
	model->aabb.applyTransform(transform);
}

void GameObject::applyTransform() {
	collider->applyTransform(transform);
	model->aabb.applyTransform(transform);
}