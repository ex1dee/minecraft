#ifndef BLOCKSDATABASE_H
#define BLOCKSDATABASE_H

#define BLOCKS_DIR "resources/blocks"

#include <map>

#include "../../textures/TextureAtlas.h"
#include "BlockType.h"

class BlocksDatabase {
	static std::map<int, BlockType*> blocks;
public:
	static TextureAtlas textureAtlas;
	static void initialize();
	static void finalize();
	static BlockType* get(int id);
};

#endif