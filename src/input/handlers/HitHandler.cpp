#include "HitHandler.h"

#include "../../gui/GUI.h"
#include "../Input.h"

void HitHandler::handle(Player& player) {
	std::shared_ptr<Block> block = player.getTargetBlock();

	if (Input::clicked(GLFW_MOUSE_BUTTON_LEFT) || (Input::clicked(GLFW_MOUSE_BUTTON_RIGHT) && block != nullptr && block->getType().isSolid)) {
		if (!player.isOpenedInventory() && !player.isOpenedBackpack())
			GUI::getRightArm()->getAnimator("hit")->playAnimation(false);

		player.getAnimator("hit")->playAnimation(false);
	}
}