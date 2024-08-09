#include "SuperFlatGenerator.h"

#include "../../chunk/Chunk.h"

void SuperFlatGenerator::generateTerrain(Chunk* chunk) {
	for (int x = 0; x < CHUNK_W; ++x) {
		for (int z = 0; z < CHUNK_D; ++z) {
			chunk->setBlock(glm::vec3(x, 0, z), STONE);
			chunk->setBlock(glm::vec3(x, 1, z), DIRT);
			chunk->setBlock(glm::vec3(x, 2, z), DIRT);
			chunk->setBlock(glm::vec3(x, 3, z), DIRT);
			chunk->setBlock(glm::vec3(x, 4, z), GRASS_BLOCK);
		}
	}
}

int SuperFlatGenerator::getMinSpawnHeight() {
	return 4;
}