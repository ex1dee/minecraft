#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>
#include <unordered_set>

#include "Chunk.h"

class World;

class ChunkManager {
	World* world;
public:
	std::unordered_map<glm::vec2, Chunk*> chunks;
	std::unordered_map<glm::vec2, Chunk*> loadedChunks;
	std::unordered_set<glm::vec2> unloadedChunks;

	ChunkManager() {}
	ChunkManager(World& world);
	~ChunkManager();

	Chunk* const load(const glm::vec2& pos);
	void unload(const glm::vec2& pos);
	void makeMesh(const glm::vec2& pos);
	Chunk* const getChunk(const glm::vec2& pos);
	bool chunkExistsAt(const glm::vec2& pos);
};

#endif