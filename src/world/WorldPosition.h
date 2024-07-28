#ifndef WORLDPOSITION_H
#define WORLDPOSITION_H

#include "chunk/Chunk.h"

struct WorldPosition {
public:
	Chunk* chunk;
	glm::vec3 localBlockPos;
};

#endif