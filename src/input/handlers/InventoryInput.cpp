#include "InventoryInput.h"

#include "../../items/DroppedItem.h"
#include "../../gui/GUIDatabase.h"
#include "../../gui/GUIManager.h"
#include "../../window/Window.h"
#include "../../player/Camera.h"
#include "../../world/World.h"
#include "../Input.h"

constexpr float THROW_ITEM_FORCE = 8.0f;

void InventoryInput::handle(Player& player) {
	InventoryItem itemOnCursor = GUIManager::getItemOnCursor(player);

	checkSwitchingSlot(player);
	checkSwitchingInventory(player);
	checkDraggingItems(player, itemOnCursor);
	checkThrowItem(player, itemOnCursor);
}

void InventoryInput::checkSwitchingSlot(Player& player) {
	for (int key = GLFW_KEY_1; key <= GLFW_KEY_9; ++key) {
		if (Input::justPressed(key)) {
			player.selectSlot(key - GLFW_KEY_1);
			player.getHotbarView().setNeedUpdate(true);

			break;
		}
	}
}

void InventoryInput::checkSwitchingInventory(Player& player) {
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

void InventoryInput::checkDraggingItems(Player& player, InventoryItem& itemOnCursor) {
	if (!itemOnCursor.isValid())
		return;

	InventoryView* view = itemOnCursor.view;
	Inventory& inventory = view->getInventory();
	ItemStack& item = *itemOnCursor.item;
	int column = itemOnCursor.column;
	int row = itemOnCursor.row;

	InventoryView* top = player.getOpenInventoryView();
	InventoryView& center = player.getBackpackView();
	InventoryView& bottom = player.getHotbarView();

	if (Input::justClicked(GLFW_MOUSE_BUTTON_LEFT)) {
		if (Input::pressed(GLFW_KEY_LEFT_SHIFT) && itemOnCursor.item->getType().material != AIR) {
			if (top != nullptr) {
				if (view == top) {
					center.getInventory().addItem(item);
					top->setItem(column, row, ItemStack(AIR));
				} else {
					top->addItem(item);
					view->setItem(column, row, ItemStack(AIR));
				}
			} else {
				if (view == &center) {
					bottom.addItem(item);
					center.setItem(column, row, ItemStack(AIR));
				} else {
					center.addItem(item);
					bottom.setItem(column, row, ItemStack(AIR));
				}
			}
		} else {
			const InventoryItem& draggedItem = player.getDraggedItem();

			if (itemOnCursor.item->getType().material != AIR) {
				if (!draggedItem.isValid()) {
					player.setDraggedItem(itemOnCursor);
					view->setItem(column, row, ItemStack(AIR));
				} else {
					std::shared_ptr<ItemStack> prevItem = std::make_shared<ItemStack>(*view->getItem(column, row));
					view->setItem(column, row, ItemStack(*draggedItem.item));
					itemOnCursor.item = prevItem;

					player.setDraggedItem(itemOnCursor);
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

void InventoryInput::checkThrowItem(Player& player, InventoryItem& itemOnCursor) {
	if (Input::justPressed(GLFW_KEY_Q)) {
		std::shared_ptr<ItemStack> item = getThrownItem(player, itemOnCursor);

		if (item->getType().material == AIR)
			return;
		
		int prevItemsAmount = item->getAmount();
		int thrownItemsAmount = Input::pressed(GLFW_KEY_LEFT_CONTROL) ? prevItemsAmount : 1;

		std::shared_ptr<ItemStack> thrownItem = std::make_shared<ItemStack>(*item);
		item->decreaseAmount(thrownItemsAmount);
		thrownItem->setAmount(prevItemsAmount - item->getAmount());

		const EntityType& droppedItemType = EntitiesDatabase::get(DROPPED_ITEM);
		Ray playerDirection = player.getViewDirection();

		std::shared_ptr<DroppedItem> droppedItem = player.getWorld()->spawnEntity<DroppedItem>(
			playerDirection.start + 0.5f * (playerDirection.direction * player.getType().colliderExtents.z - droppedItemType.colliderExtents),
			thrownItem
		);

		droppedItem->rigidBody.velocity += player.getViewDirection().direction * THROW_ITEM_FORCE + player.rigidBody.velocity;
	}
}

std::shared_ptr<ItemStack> InventoryInput::getThrownItem(Player& player, InventoryItem& itemOnCursor) {
	if (itemOnCursor.isValid())
		return itemOnCursor.item;
	
	return player.getSelectedItem();
}