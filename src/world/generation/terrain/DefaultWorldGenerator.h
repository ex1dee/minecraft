#ifndef DEFAULTWORLDGENERATOR_H
#define DEFAULTWORLDGENERATOR_H

#include "TerrainGenerator.h"

#include "../../../utils/noise/PerlinNoise2D.h"
#include "../../chunk/Chunk.h"

class DefaultWorldGenerator : public TerrainGenerator {
	PerlinNoise2D perlin;
public:
	DefaultWorldGenerator(uint8_t seed);

	void generateTerrain(Chunk* chunk) override;
	int getMinSpawnHeight() override;
};

#endif