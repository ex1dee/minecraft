#include "ItemStack.h"

ItemStack::ItemStack(Material material)
	: material(material) {

	if (getType().meta != nullptr)
		meta = std::make_unique<ItemMeta>(*getType().meta);
}

ItemStack::ItemStack(const Block& block) {
	material = block.getType().material;

	if (block.state != nullptr)
		meta = std::make_unique<BlockStateMeta>(*getType().meta, block.state);
	else
		meta = std::make_unique<ItemMeta>(*getType().meta);
}

ItemStack::ItemStack(const ItemStack& other) {
	if (other.meta != nullptr)
		meta = std::make_unique<ItemMeta>(*other.meta);

	amount = other.amount;
	material = other.material;
}

void ItemStack::setMeta(const ItemMeta& meta) {
	this->meta = std::make_unique<ItemMeta>(meta);
}