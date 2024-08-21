#include "InventoryView.h"

#include "../../gui/GUIDatabase.h"
#include "../../gui/GUIManager.h"

constexpr float ITEM_ICON_SCALE = 0.75f;

glm::vec2 InventoryView::slotSize = glm::vec3(0);

InventoryView::InventoryView(const std::shared_ptr<Inventory>& inventory, int firstRow, int lastRow)
	: inventory(inventory), firstRow(firstRow), opened(false), lastRow(glm::clamp(lastRow, 1, inventory->getRowsNumber())) {
	setupSlotSize();
	setupCenter();

	inventory->hookView(*this);
	needUpdate = true;
}

void InventoryView::setupSlotSize() {
	if (slotSize.x == 0) {
		GUIElement* rowElement = GUIDatabase::root["inventory_row"].get();
		slotSize = glm::vec2(rowElement->transform.scale) * glm::vec2(DEFAULT_SLOT_WIDTH, DEFAULT_SLOT_HEIGHT);
	}
}

void InventoryView::setupCenter() {
	center.x = 0.5f * SLOTS_IN_ROW * slotSize.x;
	center.y = 0.5f * getRowsNumber() * slotSize.y;
}

std::shared_ptr<ItemStack> InventoryView::getItem(int column, int row) const {
	return inventory->getItem(column, firstRow + row);
}

void InventoryView::addItem(const ItemStack& item) const {
	for (int i = firstRow * SLOTS_IN_ROW; i < inventory->getRowsNumber() * SLOTS_IN_ROW; ++i) {
		if (inventory->getItem(i)->getType().material == AIR) {
			inventory->setItem(i, item);

			return;
		}
	}
}

void InventoryView::setItem(int column, int row, const ItemStack& item) const {
	inventory->setItem(column, firstRow + row, item);
}

GUISector InventoryView::getGUISector(std::shared_ptr<GUIElement>& parent) const const {
	GUISector guiSector;

	for (int row = firstRow; row < lastRow; ++row) {
		std::shared_ptr<GUIElement> rowElement = createRowElement(row, parent);

		for (int column = 0; column < SLOTS_IN_ROW; ++column) {
			std::shared_ptr<GUIElement> slotElement = createSlotElement(column, row, rowElement);

			rowElement->children.emplace(slotElement->name, slotElement);
		}

		guiSector.emplace(rowElement->name, rowElement);
	}

	return guiSector;
}

std::shared_ptr<GUIElement> InventoryView::createRowElement(int row, std::shared_ptr<GUIElement>& parent) const {
	std::shared_ptr<GUIElement> rowElement = std::make_shared<GUIElement>(*GUIDatabase::root["inventory_row"]);
	
	float y = -DEFAULT_SLOT_HEIGHT * rowElement->transform.scale.y * ((row - firstRow) - 0.5f * (lastRow - 1));
	rowElement->transform.position = parent->transform.position + glm::vec3(0, y, 0);
	rowElement->transform.scale *= parent->transform.scale;
	rowElement->parent = parent;
	rowElement->visible = true;
	rowElement->name = std::to_string(row - firstRow);

	return rowElement;
}

std::shared_ptr<GUIElement> InventoryView::createSlotElement(int column, int row, std::shared_ptr<GUIElement>& rowElement) const {
	const ItemStack& item = *inventory->getItem(column, row);

	std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
	std::shared_ptr<GUIElement> element = std::make_shared<GUIElement>(
		std::to_string(column),
		Transform(),
		sprite,
		true,
		rowElement
	);

	element->sprite->texture = item.getType().texture;

	glm::vec2 texSize = element->sprite->texture.getSize();
	element->transform.scale = GUIManager::scale(
		glm::vec3(1),
		texSize.x,
		texSize.y,
		element->parent->transform.scale.x * DEFAULT_SLOT_WIDTH * ITEM_ICON_SCALE,
		element->parent->transform.scale.y * DEFAULT_SLOT_HEIGHT * ITEM_ICON_SCALE
	);

	float x = DEFAULT_SLOT_WIDTH * rowElement->transform.scale.x * (column - 0.5f * (SLOTS_IN_ROW - 1));
	element->transform.position = rowElement->transform.position + glm::vec3(x, 1.0f, 0);

	return element;
}