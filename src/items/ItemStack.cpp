#include "ItemStack.h"

#include "meta/BlockStateMeta.h"
#include "inventory/Inventory.h"
#include "../world/World.h"

ItemStack::ItemStack(Material material, int amount)
	: material(material), amount(amount) {
	assert(ItemsDatabase::contains(material));

	if (getType().meta != nullptr)
		meta = std::make_unique<ItemMeta>(*getType().meta);
}

ItemStack::ItemStack(const Block& block, int amount)
	: amount(amount) {
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
	inventory = other.inventory;
}

void ItemStack::hookInventory(Inventory* inventory) {
	this->inventory = inventory;
}

void ItemStack::setMeta(const ItemMeta& meta) {
	this->meta = std::make_unique<ItemMeta>(meta);

	inventory->updateViews();
}

std::shared_ptr<Block> ItemStack::toBlock(World* const world, const glm::vec3& position) {
	if (!BlocksDatabase::contains(material))
		return nullptr;

	std::shared_ptr<Block> block = world->setBlock(position, material);
	BlockStateMeta* blockStateMeta = (BlockStateMeta*) this->meta.get();

	if (blockStateMeta != nullptr) {
		block->state = std::make_unique<BlockState>(blockStateMeta->getState());
	}

	decreaseAmount();

	return block;
}

void ItemStack::increaseAmount(int num) {
	setAmount(amount + num);
}

void ItemStack::decreaseAmount(int num) {
	setAmount(amount - num);
}

void ItemStack::setAmount(int amount) {
	this->amount = glm::clamp(amount, 0, getType().maxAmount);

	if (this->amount == 0) {
		material = AIR;
		meta = nullptr;
	}

	inventory->updateViews();
}