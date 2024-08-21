#include "Inventory.h"

#include <glm/glm.hpp>

#include "InventoryView.h"

Inventory::Inventory(const std::wstring& title, int rowsNumber)
	: title(title), size(SLOTS_IN_ROW* this->rowsNumber), rowsNumber(glm::clamp(rowsNumber, 0, MAX_ROWS_NUMBER)) {
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
	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->getType().material == AIR) {
			setItem(i, item);

			return;
		}
	}
}

void Inventory::setItem(int index, const ItemStack& item) {
	if (isCorrectIndex(index)) {
		items[index] = std::make_shared<ItemStack>(item);

		updateViews();
	}
}

void Inventory::updateViews() {
	views.erase(std::remove(views.begin(), views.end(), nullptr), views.end());

	for (auto& view : views) {
		view->setNeedUpdate(true);
	}
}