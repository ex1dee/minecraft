#ifndef SUPERFLATGENERATOR_H
#define SUPERFLATGENERATOR_H

#include "TerrainGenerator.h"

class SuperFlatGenerator : public TerrainGenerator {
public:
	void generateTerrain(Chunk* chunk) override;
	int getMinSpawnHeight() override;
};

#endif