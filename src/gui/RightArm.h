#ifndef RIGHTARM_H
#define RIGHTARM_H

#include "../player/Player.h"
#include "../items/Item.h"

class RightArm : public Entity {
	std::shared_ptr<Item> item;
	int selectedSlot;
public:
	RightArm();

	void update(const std::shared_ptr<Player>& player, float deltaTime) override;
};

#endif