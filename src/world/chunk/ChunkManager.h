#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>
#include <unordered_set>

#include "Chunk.h"

class World;

class ChunkManager {
	World* world;
public:
	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>> chunks;
	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>> loadedChunks;
	std::unordered_set<glm::ivec2> unloadedChunks;

	ChunkManager() {}
	ChunkManager(World& world);

	std::shared_ptr<Chunk> load(const glm::ivec2& pos);
	void deleteUnloadedChunks();
	void deleteChunkAt(const glm::ivec2& pos);
	void makeMeshes(const glm::ivec2& playerChunkPos, int loadDist);
	void unloadNotVisibleChunks(const glm::ivec2& playerChunkPos, int loadDist);
	void makeMesh(const glm::ivec2& pos);
	void markAsUnloadedChunk(const glm::ivec2& pos);
	std::shared_ptr<Chunk> getChunk(const glm::ivec2& pos);
	bool chunkExistsAt(const glm::ivec2& pos);
};

#endif