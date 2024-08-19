#ifndef INVENTORYGUI_H
#define INVENTORYGUI_H

#include "../player/Player.h"

class InventoryGUI {
	static GUIElement* item_description;

	static void updateHotbar(Player& player);
	static void updateDraggedItem(Player& player);
	static void updateOpenInventory(Player& player);
	static void updateItemDesciption(Player& player, GUIElement* background);
	static void updateInventoryElement(GUIElement* element, InventoryView& view, const glm::vec3& bottomLeft);
	static void updateInventoryViewTitle(GUIElement* element, InventoryView& view, TextAlignment titleAlignment);
public:
	static void update(Player& player, bool& windowScaled);
};

#endif