#include "RightArm.h"

#include "../input/Input.h"
#include "../world/World.h"

constexpr float
RIGHT_ARM_OFFSET_FRONT = -0.4f,
RIGHT_ARM_OFFSET_UP = -0.7f,
RIGHT_ARM_OFFSET_RIGHT = 0.05f,
RIGHT_ARM_ITEM_SIZE = 0.3f;

RightArm::RightArm() 
	: Entity(EntityID::RIGHT_ARM), selectedSlot(-1) {
	
}

void RightArm::update(const std::shared_ptr<Player>& player, float deltaTime) {
	Entity::update(player, deltaTime);
}