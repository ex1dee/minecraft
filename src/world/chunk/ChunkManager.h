#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>

#include "../../utils/VecMap.h"
#include "Chunk.h"

class World;

class ChunkManager {
	World* world;
public:
	std::unordered_map<glm::vec2, Chunk*, Vec2Hash> chunks;

	ChunkManager() {}
	ChunkManager(World* world);
	~ChunkManager();

	Chunk* load(const glm::vec2& pos);
	void unload(const glm::vec2& pos);
	void makeMesh(const glm::vec2& pos, Camera& camera);
	Chunk* getChunk(const glm::vec2& pos);
	bool chunkExistsAt(const glm::vec2& pos);
};

#endif