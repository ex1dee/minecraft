#ifndef BLOCKSDATABASE_H
#define BLOCKSDATABASE_H

#define BLOCKS_DIR "resources/blocks"

#include <unordered_map>

#include "../../textures/TextureAtlas.h"
#include "BlockType.h"

class BlocksDatabase {
	static std::unordered_map<int, BlockType*> blocks;
	static TextureAtlas textureAtlas;
public:
	static void initialize();
	static void finalize();

	static const TextureAtlas& getTextureAtlas() { return textureAtlas; }
	static BlockType* get(int id) { return blocks[id]; }
};

#endif