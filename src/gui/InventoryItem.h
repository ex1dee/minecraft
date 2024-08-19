#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "../items/inventory/Inventory.h"
#include "../items/ItemStack.h"
#include "GUIElement.h"

class InventoryItem {
public:
	GUIElement* element;
	InventoryView* view;
	ItemStack* item;
	int column;
	int row;

	InventoryItem() = default;

	InventoryItem clone() const {
		InventoryItem invItem;

		invItem.element = element;
		invItem.view = view;
		invItem.item = new ItemStack(*item);
		invItem.column = column;
		invItem.row = row;

		return invItem;
	}

	bool isValid() const {
		return element != nullptr && view != nullptr && item != nullptr;
	}
};

#endif