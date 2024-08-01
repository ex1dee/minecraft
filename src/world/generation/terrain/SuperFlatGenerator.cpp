#include "SuperFlatGenerator.h"

#include "../../chunk/Chunk.h"
#include "../../../utils/random/Random.h"
#include "../../../utils/random/RandomGenerator.h"

void SuperFlatGenerator::generateTerrain(Chunk* chunk) {
	RandomGenerator gen;

	for (int x = 0; x < CHUNK_W; ++x) {
		for (int z = 0; z < CHUNK_D; ++z) {
			chunk->setBlock(glm::vec3(x, 0, z), Block(STONE));
			chunk->setBlock(glm::vec3(x, 1, z), Block(DIRT));
			chunk->setBlock(glm::vec3(x, 2, z), Block(DIRT));
			chunk->setBlock(glm::vec3(x, 3, z), Block(DIRT));
			chunk->setBlock(glm::vec3(x, 4, z), Block(GRASS_BLOCK));

			//if (gen.generateFloat() > 0.95) {
			//	chunk->setBlock(glm::vec3(x, 7, z), Block(GRASS_BLOCK));
			//}
		}
	}
}

int SuperFlatGenerator::getMinSpawnHeight() {
	return 4;
}