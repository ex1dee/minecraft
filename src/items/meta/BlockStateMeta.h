#ifndef BLOCKSTATEMETA_H
#define BLOCKSTATEMETA_H

#include "../../world/block/states/BlockState.h"
#include "ItemMeta.h"

class BlockStateMeta : public ItemMeta {
	BlockState* blockState;
public:
	BlockStateMeta(const ItemMeta& meta, const BlockState* blockState)
		: ItemMeta(meta) {
		blockState = new BlockState(*blockState);
	}
};

#endif