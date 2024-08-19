#include "Player.h"

#include "../window/Window.h"
#include "../world/World.h"
#include "Camera.h"

Player::Player(Camera& camera)
	: camera(&camera), Entity(PLAYER) {
	setupInventory();
}

Player::~Player() {
	freePointer(&inventory);
	freePointer(&backpackView);
	freePointer(&hotbarView);
	freePointer(&openInventoryView);
}

void Player::setupInventory() {
	inventory = new Inventory(L"Inventory", 4);

	backpackView = new InventoryView(*inventory, 1);
	hotbarView = new InventoryView(*inventory, 0, 1);
	hotbarView->open();
}

void Player::setFlying(bool flying) {
	this->flying = flying;

	rigidBody.setPhysicsType(flying ? PhysicsType::STATIC : PhysicsType::DYNAMIC);
}

void Player::selectSlot(int slot) {
	this->selectedSlot = glm::clamp(slot, 0, SLOTS_IN_ROW - 1);
}

void Player::setDraggedItem(const InventoryItem& item) {
	draggedItem = item.clone();
	draggedItem.element->parent->children.erase(draggedItem.element->name);
	draggedItem.element->parent = nullptr;

	GUIDatabase::root.emplace("dragged_item", draggedItem.element);
}

void Player::resetDraggedItem() {
	freePointer(&draggedItem.element);
	freePointer(&draggedItem.item);
	draggedItem.view = nullptr;

	GUIDatabase::root.erase("dragged_item");
}

void Player::openInventory(Inventory* inventory) {
	if (inventory->getRowsNumber() == 0)
		return;

	pOpenInventory = inventory;
	openInventoryView = new InventoryView(*pOpenInventory);
	openInventoryView->open();
	openBackpack();
}

void Player::openBackpack() {
	backpackView->open();
	backpackView->setNeedUpdate(true);

	Window::enableCursor();
	Window::setCursorInCenter();
	camera->setBlocked(true);
}

void Player::closeInventory() {
	openInventoryView = nullptr;
	pOpenInventory = nullptr;
	closeBackpack();
}

void Player::closeBackpack() {
	backpackView->close();
	backpackView->setNeedUpdate(true);

	Window::disableCursor();
	camera->setBlocked(false);
}

bool Player::isNeedUpdateInventoryViews() {
	return backpackView->isNeedUpdate()
		|| hotbarView->isNeedUpdate()
		|| (openInventoryView != nullptr && openInventoryView->isNeedUpdate());
}

void Player::setNeedUpdateInventoryViews(bool needUpdate) {
	hotbarView->setNeedUpdate(needUpdate);
	backpackView->setNeedUpdate(needUpdate);
	
	if (openInventoryView != nullptr)
		openInventoryView->setNeedUpdate(needUpdate);
}