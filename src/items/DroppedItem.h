#ifndef DROPPEDITEM_H
#define DROPPEDITEM_H

#include "../entity/Entity.h"
#include "ItemStack.h"

class DroppedItem : public Entity {
	std::shared_ptr<ItemStack> item;
public:
	DroppedItem(std::shared_ptr<ItemStack>& item);
};

#endif