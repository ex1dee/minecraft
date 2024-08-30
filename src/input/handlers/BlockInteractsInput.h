#ifndef BLOCKINTERACTSINPUT_H
#define BLOCKINTERACTSINPUT_H

#include "../../player/Player.h"
#include "../../world/World.h"

class BlockInteractsInput {
	static float elapsedTime;

	static glm::vec3 getAdjacentBlockPosition(Player& player, const Block& targetBlock);
public:
	static void handle(Player& player, World& world, float deltaTime);
};

#endif