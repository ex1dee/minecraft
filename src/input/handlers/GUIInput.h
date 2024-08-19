#ifndef GUIINPUT_H
#define GUIINPUT_H

#include "../../player/Player.h"

class GUIInput {
	static void checkDraggingItems(Player& player);
	static void checkSwitchingSlot(Player& player);
	static void checkSwitchingInventory(Player& player);
public:
	static void handle(Player& player);
};

#endif