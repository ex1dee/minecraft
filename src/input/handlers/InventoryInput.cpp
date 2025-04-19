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
	checkKeyboardSwitchingSlot(player);
	checkScrollSwitchingSlot(player);
}

void InventoryInput::checkKeyboardSwitchingSlot(Player& player) {
	for (int key = GLFW_KEY_1; key <= GLFW_KEY_9; ++key) {
		if (Input::justPressed(key)) {
			selectSlot(player, key - GLFW_KEY_1);
			break;
		}
	}
}

void InventoryInput::checkScrollSwitchingSlot(Player& player) {
	int scrollSign = -glm::sign(Input::getScrollYOffset());

	if (scrollSign != 0) {
		selectSlot(player, (player.getSelectedSlot() + scrollSign + 9) % 9);
	}
}

void InventoryInput::selectSlot(Player& player, int slot) {
	player.selectSlot(slot);
	player.getHotbarView().setNeedUpdate(true);

	if (player.getSelectedItem()->getType().material != AIR) {
		GUI::getRightArm()->getAnimator("switch_item")->playAnimation(false);
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
	if (Input::justClicked(GLFW_MOUSE_BUTTON_LEFT)) {
		const InventoryItem& draggedItem = player.getDraggedItem();

		if (itemOnCursor.element == nullptr) {
			if (draggedItem.isValid()) {
				throwItem(player, draggedItem.item, true);
				player.resetDraggedItem();
			}

			return;
		}

		InventoryView* view = itemOnCursor.view;
		Inventory& inventory = view->getInventory();
		ItemStack& item = *itemOnCursor.item;
		int column = itemOnCursor.column;
		int row = itemOnCursor.row;

		InventoryView* top = player.getOpenInventoryView();
		InventoryView& center = player.getBackpackView();
		InventoryView& bottom = player.getHotbarView();

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
			if (itemOnCursor.item->getType().material != AIR) {
				if (!draggedItem.isValid()) {
					player.setDraggedItem(itemOnCursor);
					view->setItem(column, row, ItemStack(AIR));
				} else {
					std::shared_ptr<ItemStack> prevItem = std::make_shared<ItemStack>(*view->getItem(column, row));
					view->setItem(column, row, ItemStack(*draggedItem.item));
					itemOnCursor.item = prevItem;

					player.resetDraggedItem();
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
		
		throwItem(player, item, Input::pressed(GLFW_KEY_LEFT_CONTROL));
	}
}

void InventoryInput::throwItem(Player& player, const std::shared_ptr<ItemStack>& item, bool throwAway) {
	if (item->getType().material == AIR)
		return;

	int prevItemsAmount = item->getAmount();
	int thrownItemsAmount = throwAway ? prevItemsAmount : 1;

	std::shared_ptr<ItemStack> thrownItem = std::make_shared<ItemStack>(*item);
	item->decreaseAmount(thrownItemsAmount);
	thrownItem->setAmount(prevItemsAmount - item->getAmount());

	Ray playerDirection = player.getViewDirection();

	std::shared_ptr<DroppedItem> droppedItem = player.getWorld()->spawnEntity<DroppedItem>(
		playerDirection.start + 0.5f * (
			playerDirection.direction * player.getType().colliderExtents.z - EntitiesDatabase::get(ITEM).colliderExtents
			),
		thrownItem
	);

	droppedItem->rigidBody.velocity += player.getViewDirection().direction * THROW_ITEM_FORCE + player.rigidBody.velocity;
}

std::shared_ptr<ItemStack> InventoryInput::getThrownItem(Player& player, InventoryItem& itemOnCursor) {
	if (itemOnCursor.isValid())
		return itemOnCursor.item;
	
	return player.getSelectedItem();
}