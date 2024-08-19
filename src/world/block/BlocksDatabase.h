#ifndef BLOCKSDATABASE_H
#define BLOCKSDATABASE_H

#include <unordered_map>

#include "../../textures/TextureLoader.h"
#include "BlockType.h"

class BlocksDatabase {
	static std::unordered_map<Material, BlockType*> blocks;
	static const TextureAtlas* textureAtlas;
public:
	static void initialize();
	static void finalize();

	static const TextureAtlas* getTextureAtlas() { return textureAtlas; }
	static const BlockType* const get(Material material) { return blocks[material]; }
};

#endif