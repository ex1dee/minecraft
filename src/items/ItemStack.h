#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include "../world/block/Block.h"
#include "meta/BlockStateMeta.h"
#include "ItemsDatabase.h"

class ItemStack {
	std::unique_ptr<ItemMeta> meta;
	Material material;
	int amount = 1;
public:
	ItemStack(Material material);
	ItemStack(const Block& block);
	ItemStack(const ItemStack& other);

	int getAmount() const { return amount; }
	bool hasMeta() const { return meta != nullptr; }
	ItemMeta& getMeta() const { return *meta; }
	const ItemType& getType() const { return ItemsDatabase::get(material); }

	void setMeta(const ItemMeta& meta);
};

#endif