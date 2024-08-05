#ifndef WORLD_H
#define WORLD_H

#define SPAWNPOINT_CHUNKS_RANGE 100

#include <thread>
#include <mutex>

#include "generation/terrain/SuperFlatGenerator.h"
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
	unsigned int seed;

	Sun* sun;

	std::atomic<bool> isRunning;
	std::mutex mainMutex;
	std::mutex configMutex;

	void makeSun();
	void renderChunks(Renderer& renderer, Player& player);
	void renderEntities(Renderer& renderer, Player& player);
	void loadChunks(Player& player, Camera& camera);
	void updateDefaultSpawnPoint(Player& player);
	void addLoadChunksThread(Player& player, Camera& camera);
public:
	World() {}
	World(TerrainGenerator* terrainGen, Player& player, Camera& camera);
	~World();

	Sun* const getSun() const { return sun; }
	TerrainGenerator& getTerrainGenerator() { return *terrainGen; }

	int getHeightAt(const glm::vec3& pos);
	Chunk* const getChunk(const glm::vec3& pos);
	Block& getBlock(const glm::vec3& pos);
	Block& getHighestBlockAt(const glm::vec3& pos);
	void updateChunks(Camera& camera);
	void updateChunk(const glm::vec3& pos);
	void render(Renderer& renderer, Player& player);
	void setBlock(const glm::vec3& pos, Block block);
	void update(Renderer& renderer, Player& player, Camera& camera);
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
	glm::vec2 getLocalChunkPosition(const glm::vec3& pos);
};

#endif