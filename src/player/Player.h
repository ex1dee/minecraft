#ifndef PLAYER_H
#define PLAYER_H

#include "../items/inventory/InventoryView.h"
#include "../math/geometry/Orientation.h"
#include "../gui/InventoryItem.h"
#include "../entity/Entity.h"

constexpr float
PLAYER_DEFAULT_SPEED = 5.75f,
PLAYER_JUMP_FORCE = 12.5f,
PLAYER_INLIQUID_JUMP_COEF = 0.5f,
PLAYER_INLIQUID_SWIM_COEF = 0.7f,
PLAYER_SPRINT_COEF = 1.5f,
PLAYER_SIDE_COEF = 0.5f,
PLAYER_FLYING_COEF = 10.0f,
PLAYER_SNEAKING_COEF = 0.35f;

class Camera;

class Player : public Entity {
	friend class MovementsInput;
	friend class PlayState;

	int selectedSlot = 0;
	bool flying = false;
	bool sneaking = false;
	bool sprinting = false;
	float speed = PLAYER_DEFAULT_SPEED;
	float jumpForce = PLAYER_JUMP_FORCE;

	std::shared_ptr<InventoryView> openInventoryView;
	std::shared_ptr<InventoryView> backpackView;
	std::shared_ptr<InventoryView> hotbarView;
	std::shared_ptr<Inventory> pOpenInventory;
	std::shared_ptr<Inventory> inventory;
	InventoryItem draggedItem;

	std::shared_ptr<Camera> camera;

	void setupInventory();
public:
	Player(std::shared_ptr<Camera>& camera);

	Camera& getCamera() const { return *camera; }
	float getWalkSpeed() const { return speed; }
	float getJumpForce() const { return jumpForce; }
	int getSelectedSlot() const { return selectedSlot; }
	bool isFlying() const { return flying; }
	bool isSneaking() const { return sneaking; }
	bool isSprinting() const { return sprinting; }
	bool isOpenedBackpack() { return backpackView->isOpened(); }
	bool isOpenedInventory() { return openInventoryView != nullptr; }
	InventoryView* getOpenInventoryView() { return openInventoryView.get(); }
	InventoryView& getBackpackView() { return *backpackView; }
	InventoryView& getHotbarView() { return *hotbarView; }
	const InventoryItem& getDraggedItem() { return draggedItem; }

	void openBackpack();
	void closeBackpack();
	void closeInventory();
	void resetDraggedItem();
	void selectSlot(int slot);
	void setFlying(bool flying);
	void setDraggedItem(const InventoryItem& item);
	void setNeedUpdateInventoryViews(bool needUpdate);
	void openInventory(const std::shared_ptr<Inventory>& inventory);
	bool isNeedUpdateInventoryViews();
};

#endif