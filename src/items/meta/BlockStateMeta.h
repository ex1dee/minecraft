#ifndef BLOCKSTATEMETA_H
#define BLOCKSTATEMETA_H

#include <memory>

#include "../../world/block/states/BlockState.h"
#include "ItemMeta.h"

class BlockStateMeta : public ItemMeta {
	std::unique_ptr<BlockState> blockState;
public:
	BlockStateMeta(const ItemMeta& meta, const std::unique_ptr<BlockState>& blockState)
		: ItemMeta(meta), blockState(std::make_unique<BlockState>(*blockState)) {

	}

	BlockState& getState() {
		return *blockState;
	}
};

#endif