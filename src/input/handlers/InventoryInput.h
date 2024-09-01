#ifndef INVENTORYINPUT_H
#define INVENTORYINPUT_H

#include "../../player/Player.h"

class InventoryInput {
	static void checkSwitchingSlot(Player& player);
	static void checkSwitchingInventory(Player& player);
	static void checkThrowItem(Player& player, InventoryItem& itemOnCursor);
	static void checkDraggingItems(Player& player, InventoryItem& itemOnCursor);
	
	static std::shared_ptr<ItemStack> getThrownItem(Player& player, InventoryItem& itemOnCursor);
public:
	static void handle(Player& player);
};

#endif