#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "../items/inventory/Inventory.h"
#include "../items/ItemStack.h"
#include "GUIElement.h"

class InventoryItem {
public:
	std::shared_ptr<GUIElement> element;
	std::shared_ptr<ItemStack> item;
	InventoryView* view;
	int column;
	int row;

	InventoryItem() = default;

	InventoryItem clone() const {
		InventoryItem invItem;

		invItem.element = element;
		invItem.view = view;
		invItem.item = std::make_unique<ItemStack>(*item);
		invItem.column = column;
		invItem.row = row;

		return invItem;
	}

	bool isValid() const {
		return element != nullptr && view != nullptr && item != nullptr;
	}
};

#endif