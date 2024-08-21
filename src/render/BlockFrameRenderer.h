#ifndef BLOCKFRAMERENDERER_H
#define BLOCKFRAMERENDERER_H

#include "../utils/random/RandomGenerator.h"
#include "../world/block/Block.h"
#include "../player/Player.h"
#include "../player/Camera.h"

class BlockFrameRenderer {
	std::shared_ptr<Block> prevBlock;
	RandomGenerator randomGen;
	Model model;

	void render(const Camera& camera);
	void createModel(const Block& block, const Player& player);
public:
	BlockFrameRenderer();

	void render(const Player& player);
};

#endif