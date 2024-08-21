#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "../player/Player.h"
#include "InventoryItem.h"
#include "GUIElement.h"

class GUIManager {
	static void getElementOnCursor(const GUISector& sector, int layer, std::pair<int, std::shared_ptr<GUIElement>>& cursorElement);
public:
	static bool isElementOnCursor(GUIElement& element);
	static InventoryItem getItemOnCursor(Player& player);
	static std::shared_ptr<GUIElement> getElementOnCursor(GUISector* sector = nullptr);
	static InventoryItem getItemByElement(Player& player, const std::shared_ptr<GUIElement>& element);
	static InventoryView* getInventoryViewByName(const std::string& name, Player& player);
	static glm::vec3 scale(const glm::vec3& vec, float oldWidth, float oldHeight, float newWidth, float newHeight);
};

#endif