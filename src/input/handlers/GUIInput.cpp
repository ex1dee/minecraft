#include "GUIInput.h"

#include "../../gui/GUIDatabase.h"
#include "../../gui/GUIManager.h"
#include "../../window/Window.h"
#include "../../player/Camera.h"
#include "../Input.h"

void GUIInput::handle(Player& player) {
	checkSwitchingSlot(player);
	checkSwitchingInventory(player);
	checkDraggingItems(player);
}

void GUIInput::checkSwitchingSlot(Player& player) {
	for (int key = GLFW_KEY_1; key <= GLFW_KEY_9; ++key) {
		if (Input::justPressed(key)) {
			player.selectSlot(key - GLFW_KEY_1);
			player.getHotbarView().setNeedUpdate(true);

			break;
		}
	}
}

void GUIInput::checkSwitchingInventory(Player& player) {
	Camera& camera = player.getCamera();

	if (Input::justPressed(GLFW_KEY_E)) {
		if (player.isOpenedBackpack()) {
			const InventoryItem& draggedItem = player.getDraggedItem();

			if (draggedItem.isValid()) {
				draggedItem.view->setItem(draggedItem.column, draggedItem.row, ItemStack(*draggedItem.item));
				player.resetDraggedItem();
			}

			player.closeInventory();
		} else {
			player.openBackpack();
		}
	}
}

void GUIInput::checkDraggingItems(Player& player) {
	InventoryItem invItem = GUIManager::getItemOnCursor(player);

	if (!invItem.isValid())
		return;

	InventoryView* view = invItem.view;
	Inventory& inventory = view->getInventory();
	ItemStack* item = invItem.item;
	int column = invItem.column;
	int row = invItem.row;

	InventoryView* top = player.getOpenInventoryView();
	InventoryView& center = player.getBackpackView();
	InventoryView& bottom = player.getHotbarView();

	if (Input::justClicked(GLFW_MOUSE_BUTTON_LEFT)) {
		if (Input::pressed(GLFW_KEY_LEFT_SHIFT) && invItem.item->type->material != AIR) {
			if (top != nullptr) {
				if (view == top) {
					center.getInventory().addItem(*item);
					top->setItem(column, row, ItemStack(AIR));
				} else {
					top->addItem(*item);
					view->setItem(column, row, ItemStack(AIR));
				}
			} else {
				if (view == &center) {
					bottom.addItem(*item);
					center.setItem(column, row, ItemStack(AIR));
				} else {
					center.addItem(*item);
					bottom.setItem(column, row, ItemStack(AIR));
				}
			}
		} else {
			const InventoryItem& draggedItem = player.getDraggedItem();

			if (invItem.item->type->material != AIR) {
				if (!draggedItem.isValid()) {
					player.setDraggedItem(invItem);
					view->setItem(column, row, ItemStack(AIR));
				} else {
					ItemStack* prevItem = new ItemStack(*view->getItem(column, row));
					view->setItem(column, row, ItemStack(*draggedItem.item));
					invItem.item = prevItem;

					player.resetDraggedItem();
					player.setDraggedItem(invItem);
				}
			} else {
				if (draggedItem.isValid()) {
					view->setItem(column, row, ItemStack(*draggedItem.item));
					player.resetDraggedItem();
				}
			}
		}
	}
}