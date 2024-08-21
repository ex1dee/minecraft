#ifndef INVENTORYGUI_H
#define INVENTORYGUI_H

#include "../player/Player.h"

class InventoryGUI {
	static std::shared_ptr<GUIElement> item_description;

	static void updateHotbar(Player& player);
	static void updateDraggedItem(Player& player);
	static void updateOpenInventory(Player& player);
	static void updateItemDesciption(Player& player);
	static void updateInventoryElement(std::shared_ptr<GUIElement>& element, const InventoryView& view, const glm::vec3& bottomLeft);
	static void updateInventoryViewTitle(std::shared_ptr<GUIElement>& element, const InventoryView& view, TextAlignment titleAlignment);
public:
	static void update(Player& player, bool& windowScaled);
};

#endif