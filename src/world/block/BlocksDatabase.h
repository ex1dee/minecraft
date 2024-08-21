#ifndef BLOCKSDATABASE_H
#define BLOCKSDATABASE_H

#include <unordered_map>

#include "../../textures/TextureLoader.h"
#include "BlockType.h"

class BlocksDatabase {
	static std::unordered_map<Material, std::unique_ptr<BlockType>> blocks;
	static std::shared_ptr<TextureAtlas> textureAtlas;
public:
	static void initialize();

	static const TextureAtlas& getTextureAtlas() { return *textureAtlas; }
	static const BlockType& get(Material material) { return *blocks[material]; }
};

#endif