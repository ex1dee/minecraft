#include "DefaultWorldGenerator.h"

#include "../../../utils/noise/PerlinNoise2D.h"
#include "../../WorldConstants.h"

DefaultWorldGenerator::DefaultWorldGenerator(uint8_t seed) {
	perlin.setup(seed);
}

void DefaultWorldGenerator::generateTerrain(Chunk* chunk) {
	for (int x = 0; x < CHUNK_W; ++x) {
		for (int z = 0; z < CHUNK_D; ++z) {
			float n = perlin.noise(chunk->getLocalPosition().x + x / 16.0f, chunk->getLocalPosition().y + z / 16.0f, 2);
			float y = (n + 1) * 50;

			//std::cout << y << " " << x << " " << z << "\n";

			chunk->setBlock(glm::vec3(x, y, z), Block(GRASS_BLOCK));

			for (int Y = y - 1; Y >= 0; --Y) {
				chunk->setBlock(glm::vec3(x, Y, z), Block(DIRT));
			}
		}
	}
}

int DefaultWorldGenerator::getMinSpawnHeight() {
	return 5;
}