#ifndef DROPPEDITEM_H
#define DROPPEDITEM_H

#include "../player/Player.h"
#include "../world/World.h"
#include "Item.h"

constexpr float DEFAULT_PICKUP_TIME_SEC = 0.75f;

class DroppedItem : public Item {
	float pickupLerpPoint = 0.0f;
	float pickupCurrentTime = 0.0f;
	float pickupTimeSec;
	glm::vec3 pickupStartPos;
	glm::vec3 rotation;
	glm::vec3 offset;

	void playLevitationAnimation(const std::shared_ptr<Player>& player, float deltaTime);
	void playPickupAnimation(const std::shared_ptr<Player>& player, float deltaTime);
public:
	DroppedItem(const std::shared_ptr<ItemStack>& item, float pickupTimeSec = DEFAULT_PICKUP_TIME_SEC);

	void update(const std::shared_ptr<Player>& player, float deltaTime) override;
	void playIdleAnimation(const std::shared_ptr<Player>& player, float deltaTime) override;
};

#endif