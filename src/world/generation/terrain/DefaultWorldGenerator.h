#ifndef DEFAULTWORLDGENERATOR_H
#define DEFAULTWORLDGENERATOR_H

#include "TerrainGenerator.h"

class DefaultWorldGenerator : public TerrainGenerator {
public:
	void generateTerrain(Chunk* chunk) override;
};

#endif