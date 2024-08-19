#include "InventoryView.h"

#include "../../gui/GUIDatabase.h"
#include "../../gui/GUIManager.h"

constexpr float ITEM_ICON_SCALE = 0.75f;

glm::vec2 InventoryView::slotSize = glm::vec3(0);

InventoryView::InventoryView(Inventory& inventory, int firstRow, int lastRow)
	: inventory(&inventory), firstRow(firstRow), opened(false), lastRow(glm::clamp(lastRow, 1, inventory.getRowsNumber())) {
	setupSlotSize();
	setupCenter();

	inventory.hookView(this);
	needUpdate = true;
}

void InventoryView::setupSlotSize() {
	if (slotSize.x == 0) {
		GUIElement* rowElement = GUIDatabase::root["inventory_row"];
		slotSize = glm::vec2(rowElement->transform.scale) * glm::vec2(DEFAULT_SLOT_WIDTH, DEFAULT_SLOT_HEIGHT);
	}
}

void InventoryView::setupCenter() {
	center.x = 0.5f * SLOTS_IN_ROW * slotSize.x;
	center.y = 0.5f * getRowsNumber() * slotSize.y;
}

ItemStack* InventoryView::getItem(int column, int row) {
	return inventory->getItem(column, firstRow + row);
}

void InventoryView::addItem(const ItemStack& item) {
	for (int i = firstRow * SLOTS_IN_ROW; i < inventory->getRowsNumber() * SLOTS_IN_ROW; ++i) {
		if (inventory->getItem(i)->type->material == AIR) {
			inventory->setItem(i, item);

			return;
		}
	}
}

void InventoryView::setItem(int column, int row, const ItemStack& item) {
	inventory->setItem(column, firstRow + row, item);
}

GUISector InventoryView::getGUISector(GUIElement& parent) {
	GUISector guiSector;

	for (int row = firstRow; row < lastRow; ++row) {
		GUIElement* rowElement = createRowElement(row, parent);

		for (int column = 0; column < SLOTS_IN_ROW; ++column) {
			GUIElement* slotElement = createSlotElement(column, row, *rowElement);

			rowElement->children.emplace(slotElement->name, slotElement);
		}

		guiSector.emplace(rowElement->name, rowElement);
	}

	return guiSector;
}

GUIElement* InventoryView::createRowElement(int row, GUIElement& parent) {
	GUIElement* rowElement = new GUIElement(*GUIDatabase::root["inventory_row"]);

	float y = -DEFAULT_SLOT_HEIGHT * rowElement->transform.scale.y * ((row - firstRow) - 0.5f * (lastRow - 1));
	rowElement->transform.position = parent.transform.position + glm::vec3(0, y, 0);
	rowElement->transform.scale *= parent.transform.scale;
	rowElement->parent = &parent;
	rowElement->visible = true;
	rowElement->name = std::to_string(row - firstRow);

	return rowElement;
}

GUIElement* InventoryView::createSlotElement(int column, int row, GUIElement& rowElement) {
	const ItemStack& item = *inventory->getItem(column, row);

	GUIElement* element = new GUIElement(
		std::to_string(column),
		Transform(),
		new Sprite,
		true,
		&rowElement
	);

	element->sprite->texture = item.type->texture;

	glm::vec2 texSize = element->sprite->texture.getSize();
	element->transform.scale = GUIManager::scale(
		glm::vec3(1),
		texSize.x,
		texSize.y,
		element->parent->transform.scale.x * DEFAULT_SLOT_WIDTH * ITEM_ICON_SCALE,
		element->parent->transform.scale.y * DEFAULT_SLOT_HEIGHT * ITEM_ICON_SCALE
	);

	float x = DEFAULT_SLOT_WIDTH * rowElement.transform.scale.x * (column - 0.5f * (SLOTS_IN_ROW - 1));
	element->transform.position = element->parent->transform.position + glm::vec3(x, 1.0f, 0);

	return element;
}