#ifndef WORLD_H
#define WORLD_H

#define SPAWNPOINT_CHUNKS_RANGE 100

#include <thread>
#include <mutex>

#include "generation/terrain/DefaultWorldGenerator.h"
#include "../entity/EntitiesDatabase.h"
#include "../entity/Entity.h"
#include "../world/World.h"
#include "chunk/ChunkManager.h"
#include "WorldPosition.h"
#include "Sun.h"

class World {
	ChunkManager* chunkManager;
	TerrainGenerator* terrainGen;
	std::vector<Chunk*> chunkUpdates;
	std::vector<std::thread> loadThreads;
	std::vector<Entity*> entities;

	glm::vec3 spawnPoint;
	uint32_t seed;

	Sun* sun;

	std::atomic<bool> isRunning;
	std::mutex mainMutex;

	void makeSun();
	void renderChunks(Renderer& renderer, Player& player);
	void renderEntities(Renderer& renderer, Player& player);
	void loadChunks(Player& player, Camera& camera);
	void updateDefaultSpawnPoint(Player& player);
	void addLoadChunksThread(Player& player, Camera& camera);

	void makeMeshes(const glm::vec2& playerPos, int loadDist);
	void unloadNotVisibleChunks(const glm::vec2& playerPos, int loadDist);
	void deleteUnloadedChunks();
public:
	World() {}
	World(Player& player, Camera& camera);
	~World();

	Sun* const getSun() const { return sun; }
	TerrainGenerator& getTerrainGenerator() { return *terrainGen; }

	int getHeightAt(const glm::vec3& pos);
	Chunk* const getChunk(const glm::vec3& pos);
	Block* getBlock(const glm::vec3& pos);
	Block* getHighestBlockAt(const glm::vec3& pos);
	void updateChunks();
	void updateChunk(const glm::vec3& pos);
	void render(Renderer& renderer, Player& player);
	void update(Renderer& renderer, Player& player);
	void setBlock(const glm::vec3& pos, BlockID blockID);
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
	glm::vec2 getLocalChunkPosition(const glm::vec3& pos);
};

#endif