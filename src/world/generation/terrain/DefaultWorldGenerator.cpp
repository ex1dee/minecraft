#include "DefaultWorldGenerator.h"

#include "../../../utils/noise/PerlinNoise2D.h"
#include "../../WorldConstants.h"

DefaultWorldGenerator::DefaultWorldGenerator(uint32_t seed) {
	landscapeNoise.setup(seed, NoiseConfig(0.0f, 1.0f, 5.0f, 0.5f, 0.003f));
}

void DefaultWorldGenerator::generateTerrain(Chunk* chunk) {
	randomGen.setSeed((int)chunk->getLocalPosition().x ^ (int)chunk->getLocalPosition().y);

	for (int x = 0; x < CHUNK_W; ++x) {
		for (int z = 0; z < CHUNK_D; ++z) {
			glm::vec3 worldPos = chunk->getWorldPosition(glm::vec3(x, 0, z));

			float noise = landscapeNoise.ridgeFBM(worldPos.x, worldPos.z, 4);
			int level = (int) floor(DWG_MIN_HEIGHT + (DWG_MAX_HEIGHT - DWG_MIN_HEIGHT) * noise);

			for (int y = 0; y <= level; ++y) {
				int dy = rangedRand(randomGen, 0, 3);

				if (y <= DWG_SEA_LEVEL + 3 + dy && y >= DWG_SEA_LEVEL - 10 - dy) {
					chunk->setBlock(glm::vec3(x, y, z), SAND);
				} else {
					if (y >= DWG_MOUNTAIN_LEVEL - dy) {
						if (randomGen.generateFloat() > (1.0f - 0.8f * (float) y / (float)DWG_MAX_HEIGHT))
							chunk->setBlock(glm::vec3(x, y, z), SNOW_BLOCK);
						else
							chunk->setBlock(glm::vec3(x, y, z), STONE);
					} else {
						if (y == level) {
							chunk->setBlock(glm::vec3(x, y, z), GRASS_BLOCK);
						} else if (y >= level - 4) {
							chunk->setBlock(glm::vec3(x, y, z), DIRT);
						} else {
							chunk->setBlock(glm::vec3(x, y, z), STONE);
						}
					}
				}
			}

			for (int y = level + 1; y <= DWG_SEA_LEVEL; ++y) {
				chunk->setBlock(glm::vec3(x, y, z), WATER);
			}
		}
	}
}

int DefaultWorldGenerator::getMinSpawnHeight() {
	return DWG_SEA_LEVEL + 1;
}