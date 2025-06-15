#ifndef BLOCK_H
#define BLOCK_H

#include <unordered_map>

#include "../../math/intersects/IntersectList.h"
#include "../../math/shapes/Ray.h"
#include "states/BlockState.h"
#include "BlocksDatabase.h"
#include "BlockType.h"

class Block {
	friend class Chunk;
	
	glm::vec3 position;
	Material material;

	Block(const Block& other) = delete;
	Block& operator=(const Block& other) = delete;
public:
	std::unique_ptr<BlockState> state;

	Block() = default;
	Block(Material material);

	const glm::vec3& getPosition() const { return position; }
	const BlockType& getType() const { return BlocksDatabase::get(material); }

	bool isLiquid() const;
	bool isCollidable() const;
	IntersectList intersect(const Ray& ray) const;

	template<typename T> static T* getMeta(const Block* const block);
};

#include "Block.inl"

#endif