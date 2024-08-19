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
public:
	const BlockType* type;
	BlockState* state;

	Block() {}
	Block(Material material);
	~Block();

	const glm::vec3& getPosition() const { return position; }

	bool isCollidable() const;
	IntersectList intersect(const Ray& ray) const;
};

#endif