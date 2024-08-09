#include "DefaultWorldGenerator.h"

#include "../../../utils/noise/PerlinNoise2D.h"
#include "../../WorldConstants.h"

DefaultWorldGenerator::DefaultWorldGenerator(uint8_t seed) {
	perlin.setup(seed);
}

void DefaultWorldGenerator::generateTerrain(Chunk* chunk) {
	for (int x = 0; x < CHUNK_W; ++x) {
		for (int z = 0; z < CHUNK_D; ++z) {
			float worldX = (chunk->getLocalPosition().x * CHUNK_W) + x;
			float worldZ = (chunk->getLocalPosition().y * CHUNK_W) + z;

			float height = 100.0f * 0.5f * (1 + perlin.noise(worldX * 0.01f, worldZ * 0.01f, 2, 0.3f));

			for (int y = 0; y <= (int)height; y++) {
				if (y == (int)height) {
					chunk->setBlock(glm::vec3(x, y, z), GRASS_BLOCK);
				} else if (y < (int)height - 3) {
					chunk->setBlock(glm::vec3(x, y, z), STONE);
				} else {
					chunk->setBlock(glm::vec3(x, y, z), DIRT);
				}
			}
		}
	}

	// TODO: delete perlin
}

int DefaultWorldGenerator::getMinSpawnHeight() {
	return 5;
}