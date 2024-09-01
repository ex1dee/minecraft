#ifndef DROPPEDITEM_H
#define DROPPEDITEM_H

#include "../entity/Entity.h"
#include "../player/Player.h"
#include "../world/World.h"
#include "ItemModel.h"
#include "ItemStack.h"

constexpr float DEFAULT_PICKUP_TIME_SEC = 0.75f;

class DroppedItem : public Entity {
	std::shared_ptr<ItemStack> item;
	float pickupLerpPoint = 0.0f;
	float pickupCurrentTime = 0.0f;
	float pickupTimeSec;
	glm::vec3 pickupStartPos;
	glm::vec3 rotation;
	glm::vec3 offset;

	void playLevitationAnimation(const std::shared_ptr<Player>& player, float deltaTime);
	void playPickupAnimation(const std::shared_ptr<Player>& player, float deltaTime);
public:
	DroppedItem(std::shared_ptr<ItemStack>& item, float pickupTimeSec = DEFAULT_PICKUP_TIME_SEC);

	void update(const std::shared_ptr<Player>& player, float deltaTime) override;
	void playAnimation(const std::shared_ptr<Player>& player, float deltaTime) override;
};

#endif