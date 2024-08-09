#ifndef BLOCK_H
#define BLOCK_H

#include "../../math/intersects/IntersectList.h"
#include "../../math/shapes/Ray.h"
#include "BlocksDatabase.h"
#include "BlockType.h"
#include "BlockID.h"

class Block {
	friend class Chunk;
	
	glm::vec3 position;
public:
	BlockType* type;

	Block() {}
	Block(BlockID id);

	const glm::vec3& getPosition() { return position; }
	bool isCollidable() { return this != nullptr && type->colliders.size(); }

	IntersectList intersect(const Ray& ray) const;
};

#endif