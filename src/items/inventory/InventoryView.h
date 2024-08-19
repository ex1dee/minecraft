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

	Inventory* inventory;
	bool needUpdate;
	glm::vec2 center;
	int firstRow;
	int lastRow;
	bool opened;

	void setupCenter();
	void setupSlotSize();
	GUIElement* createRowElement(int row, GUIElement& parent);
	GUIElement* createSlotElement(int column, int row, GUIElement& rowElement);
public:
	InventoryView(Inventory& inventory, int firstRow = 0, int rowsNumber = MAX_ROWS_NUMBER);

	void open() { opened = true; }
	void close() { opened = false; }
	void setNeedUpdate(bool needUpdate) { this->needUpdate = needUpdate; }

	bool isOpened() { return opened; }
	bool isNeedUpdate() { return needUpdate; }
	int getRowsNumber() { return lastRow - firstRow; }
	Inventory& getInventory() { return *inventory; }
	const glm::vec2& getSectorCenter() { return center; }

	static const glm::vec2& getSlotSize() { return slotSize; }

	ItemStack* getItem(int column, int row);
	GUISector getGUISector(GUIElement& parent);
	void setItem(int column, int row, const ItemStack& item);
	void addItem(const ItemStack& item);
};

#endif