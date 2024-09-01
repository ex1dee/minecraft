#include "Entity.h"

#include "../physics/collision/BoxBoxCollision.h"
#include "../physics/collider/BoxCollider.h"
#include "../world/RayTracing.h"

constexpr float ENTITY_MAX_TARGET_BLOCK_DIST = 5.0f;

Entity::Entity(EntityID id)
	: GameObject(), id(id) {
	hookWorld(world);

	const EntityType& type = getType();

	modelTransform = type.modelTransform;

	Transform transform;
	transform.position = type.colliderPosition;

	collider = std::make_unique<BoxCollider>(type.colliderExtents, transform);

	if (type.model != nullptr) {
		model = type.model;
		model->aabb.extents = type.colliderExtents;
	}

	if (type.physics) {
		collidesWithObjects = type.collidesWithObjects;

		rigidBody.setPhysicsType(PhysicsType::DYNAMIC);
		rigidBody.mass = type.mass;

		PhysicsEngine::addObject(*this);
	}
}

bool Entity::isOnGround() const {
	glm::vec3 extents = ((BoxCollider*) collider.get())->getExtents();
	glm::vec3 colliderCenter = transform.position + collider->getPosition();

	std::shared_ptr<Block> block1 = world->getBlock(colliderCenter + glm::vec3(extents.x, -0.00001f, 0));
	std::shared_ptr<Block> block2 = world->getBlock(colliderCenter + glm::vec3(extents.x, -0.00001f, extents.z));
	std::shared_ptr<Block> block3 = world->getBlock(colliderCenter + glm::vec3(0, -0.00001f, extents.z));
	std::shared_ptr<Block> block4 = world->getBlock(colliderCenter + glm::vec3(0, -0.00001f, 0));

	return (block1 != nullptr && block1->isCollidable())
		|| (block2 != nullptr && block2->isCollidable())
		|| (block3 != nullptr && block3->isCollidable())
		|| (block4 != nullptr && block4->isCollidable());
}

std::shared_ptr<Block> Entity::getTargetBlock() const {
	return RayTracing::getNearestBlock(*world, getViewDirection(), ENTITY_MAX_TARGET_BLOCK_DIST);
}

Ray Entity::getViewDirection() const {
	return Ray(getEyesPosition(), orientation.front);
}

Liquid* Entity::getLiquidAtEyes() const {
	std::shared_ptr<Block> block = world->getBlock(getEyesPosition() - glm::vec3(0, 0.075f, 0));

	if (block != nullptr)
		return ((Liquid*)block->getType().meta.get());

	return nullptr;
}

glm::vec3 Entity::getEyesPosition() const {
	return transform.position + getType().eyesOffset;
}

glm::vec3 Entity::getColliderCenter() const {
	return transform.position + getType().colliderPosition + getType().colliderExtents * 0.5f;
}

bool Entity::isAtBlock(const glm::vec3& position, const BlockType& type) const {
	return isCollidesWithBlock(position, type);
}

bool Entity::isAtBlock(const glm::vec3& position) const {
	std::shared_ptr<Block> block = world->getBlock(position);
	if (block == nullptr)
		return false;

	return isCollidesWithBlock(position, block->getType());
}

bool Entity::isCollidesWithBlock(const glm::vec3& position, const BlockType& type) const {
	Transform transform(position);

	for (auto& blockBox : type.colliders) {
		blockBox->updateTransform(transform);

		Collision collision = BoxBoxCollision::detect(*blockBox, *(BoxCollider*)collider.get());

		if (collision.collided && collision.depth != 0)
			return true;
	}

	return false;
}

bool Entity::needUpdate() const {
	std::shared_ptr<Chunk> chunk = world->getChunk(transform.position);

	if (transform.position.y < 0 || transform.position.y >= CHUNK_H) {
		world->despawnEntity(*this);

		return false;
	}

	return chunk != nullptr && chunk->isLoaded();
}