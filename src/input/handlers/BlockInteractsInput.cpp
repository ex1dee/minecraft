#include "BlockInteractsInput.h"

#include "../Input.h"

constexpr float BLOCK_INTERACT_INTERVAL_SEC = 0.5f;

float BlockInteractsInput::elapsedTime = 0.0f;

void BlockInteractsInput::handle(Player& player, World& world, float deltaTime) {
	std::shared_ptr<Block> block = player.getTargetBlock();
	
	if (block == nullptr || block->getType().material == AIR || player.isOpenedBackpack())
		return;

	bool leftClicked = Input::clicked(GLFW_MOUSE_BUTTON_LEFT);
	bool rightClicked = Input::clicked(GLFW_MOUSE_BUTTON_RIGHT);

	if (elapsedTime >= BLOCK_INTERACT_INTERVAL_SEC || (!leftClicked && !rightClicked)) {
		elapsedTime = 0;

		return;
	} else {
		if (elapsedTime != 0) {
			leftClicked = false;
			rightClicked = false;
		}

		elapsedTime += deltaTime;
	}

	glm::vec3 blockPos = block->getPosition();

	if (leftClicked && block->getType().isSolid) {
		world.setBlock(blockPos, Material::AIR);
	} else if (rightClicked) {
		glm::vec3 adjacentBlockPos = getAdjacentBlockPosition(player, *block);
		std::shared_ptr<Block> oldAdjacentBlock = world.getBlock(adjacentBlockPos);

		if (adjacentBlockPos.y < 0 || adjacentBlockPos.y >= CHUNK_H
		 || (oldAdjacentBlock != nullptr && oldAdjacentBlock->getType().isSolid))
			return;

		std::shared_ptr<ItemStack> selectedItem = player.getSelectedItem();
		Material material = selectedItem->getType().material;
		
		if (material != AIR) {
			if (BlocksDatabase::contains(material) && !player.isAtBlock(adjacentBlockPos, BlocksDatabase::get(material))) {
				selectedItem->toBlock(&world, adjacentBlockPos);
			}
		}
	}
}

glm::vec3 BlockInteractsInput::getAdjacentBlockPosition(Player& player, const Block& targetBlock) {
	glm::vec3 targetBlockPosition = targetBlock.getPosition();
	glm::vec3 targetBlockCenter = targetBlockPosition + glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 intersect = targetBlock.intersect(player.getViewDirection()).getNearestTo(player.transform.position);

	Transform transform(targetBlockPosition);
	glm::vec3 rectCenter(0);

	for (auto& collider : targetBlock.getType().colliders) {
		for (const Rect& rect : collider->getRectangles(transform)) {
			if (rect.isPointInside(intersect)) {
				rectCenter = rect.getCenter();

				break;
			}
		}

		if (glm::length(rectCenter) != 0) {
			break;
		}
	}

	return floor(targetBlockCenter + glm::normalize(rectCenter - targetBlockCenter));
}