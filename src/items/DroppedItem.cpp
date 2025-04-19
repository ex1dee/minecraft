#include "DroppedItem.h"

#include "../physics/PhysicsConstants.h"

constexpr float
MAX_ITEM_OFFSET_Y = 0.5f,
ITEM_ROTATION_SPEED = 0.05f,
PICKUP_DURATION = 0.125f,
START_PICKUP_RADIUS = 2.0f;

DroppedItem::DroppedItem(const std::shared_ptr<ItemStack>& item, float pickupTimeSec)
	: Item(item), pickupTimeSec(pickupTimeSec), rotation(glm::vec3(0)), offset(getType().modelTransform.position) {
	
}

void DroppedItem::update(const std::shared_ptr<Player>& player, float deltaTime) {
	if (isOnGround())
		rigidBody.velocity = glm::vec3(0);

	glm::vec3 colliderCenter = getColliderCenter();

	if (isAtBlock(colliderCenter)) {
		world->despawnEntity(*this);

		return;
	}
}

void DroppedItem::playIdleAnimation(const std::shared_ptr<Player>& player, float deltaTime) {
	playLevitationAnimation(player, deltaTime);
	playPickupAnimation(player, deltaTime);
}

void DroppedItem::playLevitationAnimation(const std::shared_ptr<Player>& player, float deltaTime) {
	rotation.y += ITEM_ROTATION_SPEED;

	if (rotation.y > 360.0f)
		rotation.y -= 360.0f;

	float defaultOffset = getType().modelTransform.position.y;
	offset.y = defaultOffset + glm::sin(glm::radians(rotation.y * 10.0f)) * (defaultOffset * 0.5f);

	modelTransform.rotation.y = rotation.y;
	modelTransform.position = offset;
}

void DroppedItem::playPickupAnimation(const std::shared_ptr<Player>& player, float deltaTime) {
	glm::vec3 colliderCenter = player->getColliderCenter();

	if (pickupLerpPoint == 0) {
		if (glm::distance(colliderCenter, transform.position) <= START_PICKUP_RADIUS) {
			pickupCurrentTime += deltaTime;
		} else {
			pickupCurrentTime = 0.0f;
		}

		if (pickupCurrentTime >= pickupTimeSec) {
			pickupStartPos = transform.position;
			pickupLerpPoint += deltaTime;

			PhysicsEngine::removeObject(*this);
		}
	} else {
		if (pickupLerpPoint >= 1) {
			player->getInventory().addItem(*item);
			world->despawnEntity(*this);
		} else {
			transform.position = Mathf::lerp(pickupStartPos, colliderCenter - getType().colliderExtents * 0.5f, pickupLerpPoint);

			pickupLerpPoint += deltaTime / PICKUP_DURATION;
		}
	}
}