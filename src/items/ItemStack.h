#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include "meta/BlockStateMeta.h"

#include "../world/block/Block.h"
#include "ItemsDatabase.h"

class Inventory;
class World;

class ItemStack {
	friend class Inventory;

	Inventory* inventory = nullptr;
	std::unique_ptr<ItemMeta> meta;
	Material material;
	int amount;

	void hookInventory(Inventory* inventory);
public:
	ItemStack(Material material, int amount = 1);
	ItemStack(const Block& block, int amount = 1);
	ItemStack(const ItemStack& other);

	int getAmount() const { return amount; }
	bool hasMeta() const { return meta != nullptr; }
	ItemMeta& getMeta() const { return *meta; }
	const ItemType& getType() const { return ItemsDatabase::get(material); }

	void setAmount(int amount);
	void setMeta(const ItemMeta& meta);
	std::shared_ptr<Block> toBlock(World* const world, const glm::vec3& position);
};

#endif