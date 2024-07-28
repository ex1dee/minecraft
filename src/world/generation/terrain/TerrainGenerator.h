#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

class Chunk;

class TerrainGenerator {
public:
	virtual void generateTerrain(Chunk* chunk) = 0;
	virtual int getMinSpawnHeight() = 0;
};

#endif