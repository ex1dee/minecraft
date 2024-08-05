#ifndef BLOCKFRAMERENDERER_H
#define BLOCKFRAMERENDERER_H

#include "../utils/random/RandomGenerator.h"
#include "../world/block/Block.h"
#include "../player/Player.h"
#include "../player/Camera.h"

#define BLOCKFRAME_LINE_WIDTH 3.0f

class BlockFrameRenderer {
	RandomGenerator randomGen;
	Block* prevBlock;
	Model* model;

	void render(Camera* camera);
	void createModel(Block* block, Player& player);
public:
	BlockFrameRenderer();

	void render(Camera* camera, Player& player);
};

#endif