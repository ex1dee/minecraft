#include "ItemStack.h"

ItemStack::ItemStack(Material material) {
	type = ItemsDatabase::get(material);

	if (type->meta != nullptr)
		meta = new ItemMeta(*type->meta);
}

ItemStack::ItemStack(const Block& block) {
	type = ItemsDatabase::get(block.type->material);

	if (block.state != nullptr)
		meta = new BlockStateMeta(*type->meta, block.state);
	else
		meta = new ItemMeta(*type->meta);
}

ItemStack::ItemStack(const ItemStack& other) {
	if (other.meta != nullptr)
		meta = new ItemMeta(*other.meta);

	amount = other.amount;
	type = other.type;
}

ItemStack::~ItemStack() {
	free(meta);
}

void ItemStack::setMeta(const ItemMeta& meta) {
	if (this->meta != nullptr)
		freePointer(&this->meta);

	this->meta = new ItemMeta(meta);
}