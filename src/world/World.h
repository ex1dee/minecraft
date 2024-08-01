#ifndef WORLD_H
#define WORLD_H

#define SPAWNPOINT_CHUNKS_RANGE 100

#include <thread>
#include <mutex>

#include "generation/terrain/SuperFlatGenerator.h"
#include "chunk/ChunkManager.h"
#include "../world/World.h"
#include "WorldPosition.h"

class World {
	ChunkManager* chunkManager;
	TerrainGenerator* terrainGen;
	std::vector<Chunk*> chunkUpdates;
	std::vector<std::thread> loadThreads;
	glm::vec3 spawnPoint;
	unsigned int seed;

	std::atomic<bool> isRunning;
	std::mutex mainMutex;
public:
	World() {}
	World(TerrainGenerator* terrainGen, Player& player, Camera& camera);
	~World();

	int getHeightAt(const glm::vec3& pos);
	Block& getBlock(const glm::vec3& pos);
	Block& getHighestBlockAt(const glm::vec3& pos);
	void loadChunks(Player& player, Camera& camera);
	void updateChunks(Camera& camera);
	void updateChunk(const glm::vec3& pos);
	void setSpawnPoint(Player& player);
	void render(Renderer& renderer, Camera& camera);
	void setBlock(const glm::vec3& pos, Block block);
	void update(Renderer& renderer, Player& player, Camera& camera);
	TerrainGenerator& getTerrainGenerator();
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
	glm::vec2 getChunkPosition(const glm::vec3& pos);
};

#endif