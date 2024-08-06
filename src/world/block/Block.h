#ifndef BLOCK_H
#define BLOCK_H

#include "../../math/intersects/IntersectList.h"
#include "../../math/shapes/Ray.h"
#include "BlocksDatabase.h"
#include "BlockType.h"
#include "BlockID.h"

class Block {
public:
	glm::vec3 position;
	BlockType* type;

	Block() {}
	Block(BlockID id);

	IntersectList intersect(const Ray& ray) const;
};

#endif