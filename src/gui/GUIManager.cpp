#include "GUIManager.h"

#include "../math/shapes/Rect.h"
#include "../window/Window.h"
#include "GUIDatabase.h"

glm::vec3 GUIManager::scale(const glm::vec3& vec, float oldWidth, float oldHeight, float newWidth, float newHeight) {
	return glm::vec3(
		(newWidth / oldWidth) * vec.x,
		(newHeight / oldHeight) * vec.y,
		vec.z
	);
}

InventoryItem GUIManager::getItemOnCursor(Player& player) {
	std::shared_ptr<GUIElement> background = GUIDatabase::root["inventory"]->children["background"];
	std::shared_ptr<GUIElement> cursorElement = GUIManager::getElementOnCursor(&background->children);

	if (cursorElement == nullptr)
		return InventoryItem();

	return GUIManager::getItemByElement(player, cursorElement);
}

std::shared_ptr<GUIElement> GUIManager::getElementOnCursor(GUISector* sector) {
	if (sector == nullptr)
		sector = &GUIDatabase::root;

	std::pair<int, std::shared_ptr<GUIElement>> cursorElement;
	cursorElement.first = -1;

	getElementOnCursor(*sector, 0, cursorElement);

	return cursorElement.second;
}

void GUIManager::getElementOnCursor(const GUISector& sector, int layer, std::pair<int, std::shared_ptr<GUIElement>>& cursorElement) {
	for (auto pair : sector) {
		std::shared_ptr<GUIElement> element = pair.second;

		if (!element->visible)
			continue;

		getElementOnCursor(element->children, layer + 1, cursorElement);

		if (layer > cursorElement.first && element->name != "dragged_item" && isElementOnCursor(*element)) {
			cursorElement.first = layer;
			cursorElement.second = element;
		}
	}
}

bool GUIManager::isElementOnCursor(GUIElement& element) {
	if (!element.hasTexture())
		return false;

	glm::vec3 cursorPos = glm::vec3(Window::getCursorPosRelativeToCenter(), GUI_ELEMENT_Z);
	Rect rect = element.sprite->getRect();

	return rect.isPointInside(cursorPos);
}

InventoryItem GUIManager::getItemByElement(Player& player, const std::shared_ptr<GUIElement>& element) {
	InventoryItem result;

	if (element == nullptr || element->parent == nullptr || element->parent->parent == nullptr)
		return result;

	int column, row;

	try {
		column = std::stoi(element->name);
		row = std::stoi(element->parent->name);
	} catch (...) {
		return result;
	}

	InventoryView* view = getInventoryViewByName(element->parent->parent->name, player);

	if (view == nullptr)
		return result;

	result.item = view->getItem(column, row);
	result.element = element;
	result.view = view;
	result.column = column;
	result.row = row;

	return result;
}

InventoryView* GUIManager::getInventoryViewByName(const std::string& name, Player& player) {
	if (name == "top")
		return player.getOpenInventoryView();
	else if (name == "center")
		return &player.getBackpackView();
	else if (name == "bottom")
		return &player.getHotbarView();
	else
		return nullptr;
}