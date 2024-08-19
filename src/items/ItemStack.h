#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include "../world/block/Block.h"
#include "meta/BlockStateMeta.h"
#include "ItemsDatabase.h"

class ItemStack {
	ItemMeta* meta = nullptr;
	int amount = 1;
public:
	const ItemType* type;

	ItemStack(Material material);
	ItemStack(const Block& block);
	ItemStack(const ItemStack& other);
	~ItemStack();

	int getAmount() { return amount; }
	const ItemMeta* getMeta() { return meta; }
	bool hasMeta() { return meta != nullptr; }

	void setMeta(const ItemMeta& meta);
};

#endif