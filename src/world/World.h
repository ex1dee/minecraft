#ifndef WORLD_H
#define WORLD_H

#include <thread>
#include <mutex>

#include "../entity/EntitiesDatabase.h"
#include "../render/fog/Fog.h"
#include "../player/Player.h"
#include "generation/terrain/DefaultWorldGenerator.h"
#include "generation/terrain/SuperFlatGenerator.h"
#include "chunk/ChunkManager.h"
#include "WorldPosition.h"
#include "Clouds.h"
#include "Sun.h"

class World {
	TerrainGenerator* terrainGen;
	ChunkManager chunkManager;

	std::vector<Chunk*> chunkUpdates;
	std::vector<std::thread> loadThreads;
	std::vector<Entity*> entities;

	glm::vec3 spawnPoint;
	uint32_t seed;

	Renderer* renderer;
	Player* player;

	Clouds* clouds;
	Sun* sun;
	Fog fog;

	std::atomic<bool> isRunning;
	std::mutex mainMutex;

	void loadChunks();
	void renderChunks();
	void renderEntities();
	void addLoadChunksThread();
	void deleteUnloadedChunks();
	void updateDefaultSpawnPoint();
	void deleteChunkAt(const glm::vec2& chunkPos);
	void makeMeshes(const glm::vec2& chunkPos, int loadDist);
	void unloadNotVisibleChunks(const glm::vec2& chunkPos, int loadDist);
public:
	World(Player& player, Renderer& renderer);
	~World();

	const Sun& getSun() { return *sun; }
	const Clouds& getClouds() { return *clouds; }
	TerrainGenerator& getTerrainGenerator() { return *terrainGen; }

	const Fog& getFog();
	int getHeightAt(const glm::vec3& pos);
	Chunk* const getChunk(const glm::vec3& pos);
	Block* getBlock(const glm::vec3& pos);
	Block* getHighestBlockAt(const glm::vec3& pos);
	void render();
	void updateChunks();
	void update(float deltaTime);
	void updateChunk(const glm::vec3& pos);
	void setBlock(const glm::vec3& pos, BlockID blockID);
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
	glm::vec2 getLocalChunkPosition(const glm::vec3& pos);
};

#endif