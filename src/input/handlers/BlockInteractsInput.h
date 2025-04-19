#ifndef BLOCKINTERACTSINPUT_H
#define BLOCKINTERACTSINPUT_H

#include "../../player/Player.h"
#include "../../world/World.h"

class BlockInteractsInput {
	static float elapsedTime;

	static void breakBlock(Player& player, World& world, const std::shared_ptr<Block>& targetBlock);
	static void placeBlock(Player& player, World& world, const std::shared_ptr<Block>& targetBlock);
	static glm::vec3 getAdjacentBlockPosition(Player& player, const Block& targetBlock);
public:
	static void handle(Player& player, World& world, float deltaTime);
};

#endif