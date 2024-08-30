#ifndef INVENTORYVIEW_H
#define INVENTORYVIEW_H

#include "../../gui/GUIElement.h"
#include "../../text/Text2D.h"
#include "Inventory.h"

constexpr float
DEFAULT_SLOT_WIDTH = 20,
DEFAULT_SLOT_HEIGHT = 20;

class InventoryView {
	static glm::vec2 slotSize;

	std::shared_ptr<Inventory> inventory;
	bool needUpdate;
	glm::vec2 center;
	int firstRow;
	int lastRow;
	bool opened;

	void setupCenter();
	void setupSlotSize();
	std::shared_ptr<GUIElement> createRowElement(int row, std::shared_ptr<GUIElement>& parent) const;
	std::shared_ptr<GUIElement> createSlotElement(int column, int row, std::shared_ptr<GUIElement>& rowElement) const;
	void addItemAmountElement(
		const ItemStack& item, std::shared_ptr<GUIElement>& slotElement, std::shared_ptr<GUIElement>& rowElement
	) const;
public:
	InventoryView(const std::shared_ptr<Inventory>& inventory, int firstRow = 0, int rowsNumber = MAX_ROWS_NUMBER);

	void open() { opened = true; }
	void close() { opened = false; }
	void setNeedUpdate(bool needUpdate) { this->needUpdate = needUpdate; }

	bool isOpened() const { return opened; }
	bool isNeedUpdate() const { return needUpdate; }
	int getRowsNumber() const { return lastRow - firstRow; }
	Inventory& getInventory() const { return *inventory; }
	const glm::vec2& getSectorCenter() const { return center; }

	static const glm::vec2& getSlotSize() { return slotSize; }

	std::shared_ptr<ItemStack> getItem(int column, int row) const;
	GUISector getGUISector(std::shared_ptr<GUIElement>& parent) const;
	void setItem(int column, int row, const ItemStack& item) const;
	void addItem(const ItemStack& item) const;
};

#endif