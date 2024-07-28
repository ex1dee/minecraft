#ifndef BLOCK_H
#define BLOCK_H

#include "BlockID.h"
#include "BlockType.h"
#include "BlocksDatabase.h"

class Block {
public:
	BlockType* type;

	Block() = default;

	Block(BlockID id) {
		type = BlocksDatabase::get(id);
	}
};

#endif