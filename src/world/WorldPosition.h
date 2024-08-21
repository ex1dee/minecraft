#ifndef WORLDPOSITION_H
#define WORLDPOSITION_H

#include "chunk/Chunk.h"

struct WorldPosition {
public:
	std::shared_ptr<Chunk> chunk;
	glm::vec3 localBlockPos;
};

#endif