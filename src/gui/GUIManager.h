#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "../player/Player.h"
#include "InventoryItem.h"
#include "GUIElement.h"

class GUIManager {
	static bool isElementOnCursor(GUIElement* element);
	static void getElementOnCursor(const GUISector& sector, int layer, std::pair<int, GUIElement*>& cursorElement);
public:
	static void deleteSector(GUISector& sector);
	static InventoryItem getItemOnCursor(Player& player);
	static GUIElement* getElementOnCursor(GUISector* sector = nullptr);
	static InventoryItem getItemByElement(Player& player, GUIElement* element);
	static InventoryView* getInventoryViewByName(const std::string& name, Player& player);
	static glm::vec3 scale(const glm::vec3& vec, float oldWidth, float oldHeight, float newWidth, float newHeight);
};

#endif