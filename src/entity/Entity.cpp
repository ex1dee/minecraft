#include "Entity.h"

#include "../physics/collision/BoxBoxCollision.h"
#include "../physics/collider/BoxCollider.h"
#include "../sounds/SoundEngine.h"
#include "../world/RayTracing.h"

constexpr float ENTITY_MAX_TARGET_BLOCK_DIST = 5.0f;

Entity::Entity(EntityID id)
	: GameObject(), id(id) {
	hookWorld(world);

	const EntityType& type = getType();
	isInCameraSpace = type.isInCameraSpace;
	modelTransform = type.modelTransform;

	for (auto pair : type.animations) { 
		animators.emplace(pair.first, Animator(pair.second));
	}

	Transform transform;
	transform.position = type.colliderPosition;
	collider = std::make_unique<BoxCollider>(type.colliderExtents, transform);

	setModel(type.model);

	if (type.physics) {
		collidesWithObjects = type.collidesWithObjects;

		rigidBody.setPhysicsType(PhysicsType::DYNAMIC);
		rigidBody.mass = type.mass;

		PhysicsEngine::addObject(*this);
	}
}

void Entity::update(const std::shared_ptr<Player>& player, float deltaTime) {
	
}

bool Entity::isOnGround() const {
	for (const auto& block : getBlocksUnderfoot()) {
		if (block != nullptr && block->isCollidable())
			return true;
	}

	return false;
}

std::shared_ptr<Block> Entity::getBlockUnderfoot() const {
	std::shared_ptr<Block> nearestBlock = nullptr;
	float minDist = FLT_MAX;

	for (const auto& block : getBlocksUnderfoot()) {
		if (block != nullptr) {
			float dist = glm::distance(block->getPosition(), transform.position);

			if (dist < minDist) {
				minDist = dist;
				nearestBlock = block;
			}
		}
	}

	return nearestBlock;
}

std::array<std::shared_ptr<Block>, 4> Entity::getBlocksUnderfoot() const {
	glm::vec3 extents = ((BoxCollider*)collider.get())->getExtents();
	glm::vec3 colliderCenter = transform.position + collider->getPosition();

	return {
		world->getBlock(colliderCenter + glm::vec3(extents.x, GROUND_OFFSET_Y, 0)),
		world->getBlock(colliderCenter + glm::vec3(extents.x, GROUND_OFFSET_Y, extents.z)),
		world->getBlock(colliderCenter + glm::vec3(0, GROUND_OFFSET_Y, extents.z)),
		world->getBlock(colliderCenter + glm::vec3(0, GROUND_OFFSET_Y, 0))
	};
}

std::shared_ptr<Block> Entity::getTargetBlock() const {
	return RayTracing::getNearestBlock(*world, getViewDirection(), ENTITY_MAX_TARGET_BLOCK_DIST);
}

Ray Entity::getViewDirection() const {
	return Ray(getEyesPosition(), orientation.getFront());
}

Liquid* Entity::getLiquidAtEyes() const {
	std::shared_ptr<Block> block = getBlockAtEyes();

	if (block != nullptr)
		return ((Liquid*)block->getType().meta.get());

	return nullptr;
}

std::shared_ptr<Block> Entity::getBlockAtEyes() const {
	return world->getBlock(getEyesPosition() - glm::vec3(0, 0.075f, 0));
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
		blockBox->applyTransform(transform);

		Collision collision = BoxBoxCollision::detect(*blockBox, *(BoxCollider*)collider.get());

		if (collision.collided && collision.depth != 0)
			return true;
	}

	return false;
}

bool Entity::needUpdate() const {
	if (isInCameraSpace)
		return true;

	if (transform.position.y < 0 || transform.position.y >= CHUNK_H) {
		world->despawnEntity(*this);

		return false;
	}

	return isAtLoadedChunk();
}

void Entity::setModel(const std::shared_ptr<Model>& model) {
	if (model == nullptr)
		return;

	this->model = model;
	this->model->aabb.extents = getType().colliderExtents;
}

std::vector<glm::mat4> Entity::updateAnimators() {
	if (!hasAnimators())
		return {};

	int bonesNumber = animators.begin()->second.boneMatrices.size();
	std::vector<glm::mat4> boneMatrices(bonesNumber, glm::mat4(1.0f));
	
	for (auto& pair : animators) {
		Animator& animator = pair.second;
		animator.update();

		assert(animator.boneMatrices.size() == bonesNumber);
		
		for (int i = 0; i < bonesNumber; ++i) {
			boneMatrices[i] *= animator.boneMatrices[i];
		}
	}

	return boneMatrices;
}