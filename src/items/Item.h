#ifndef ITEM_H
#define ITEM_H

#include "../entity/Entity.h"
#include "ItemModel.h"
#include "ItemStack.h"

class Item : public Entity {
protected:
	std::shared_ptr<ItemStack> item;
public:
	Item(const std::shared_ptr<ItemStack>& item);
};

#endif