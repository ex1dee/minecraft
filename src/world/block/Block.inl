#include "Block.h"

template<typename T>
static T* Block::getMeta(const Block* const block) {
	if (block != nullptr)
		return ((T*)block->getType().meta.get());

	return nullptr;
}