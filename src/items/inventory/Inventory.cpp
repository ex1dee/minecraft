#include "Inventory.h"

#include <glm/glm.hpp>

#include "InventoryView.h"

Inventory::Inventory(const std::wstring& title, int rowsNumber)
	: title(title), size(SLOTS_IN_ROW * this->rowsNumber), rowsNumber(glm::clamp(rowsNumber, 0, MAX_ROWS_NUMBER)) {
	items.reserve(size);

	for (int i = 0; i < size; ++i) {
		items.push_back(std::make_shared<ItemStack>(AIR));
	}
}

std::shared_ptr<ItemStack> Inventory::getItem(int column, int row) const {
	int index = getIndex(column, row);
	
	return getItem(index);
}

std::shared_ptr<ItemStack> Inventory::getItem(int index) const {
	if (isCorrectIndex(index)) {
		return items[index];
	} else {
		return nullptr;
	}
}

void Inventory::hookView(InventoryView& view){
	views.push_back(&view);
}

void Inventory::setItem(int column, int row, const ItemStack& item) {
	int index = getIndex(column, row);

	setItem(index, item);
}

void Inventory::addItem(const ItemStack& item) {
	if (addItem(item, item.getAmount()))
		return;

	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->getType().material == AIR) {
			setItem(i, item);

			return;
		}
	}
}

bool Inventory::addItem(const ItemStack& item, int amount) {
	if (amount <= 0)
		return false;

	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->getType().material == item.getType().material && items[i]->getAmount() < items[i]->getType().maxAmount) {
			int newAmount = glm::min(items[i]->getAmount() + amount, items[i]->getType().maxAmount);
			int prevAmount = items[i]->getAmount();
			items[i]->setAmount(newAmount);

			addItem(item, prevAmount + amount - items[i]->getType().maxAmount);

			return true;
		}
	}

	return false;
}

void Inventory::setItem(int index, const ItemStack& item) {
	if (item.amount == 0)
		return;

	if (isCorrectIndex(index)) {
		items[index] = std::make_shared<ItemStack>(item);
		items[index]->hookInventory(this);

		updateViews();
	}
}

void Inventory::updateViews() {
	views.erase(std::remove(views.begin(), views.end(), nullptr), views.end());

	for (auto& view : views) {
		view->setNeedUpdate(true);
	}
}