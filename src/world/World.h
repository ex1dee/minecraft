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
	std::vector<std::shared_ptr<Chunk>> chunkUpdates;
	std::vector<std::thread> loadThreads;
	std::vector<Entity*> entities;

	glm::vec3 spawnPoint;
	uint32_t seed;

	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;

	std::unique_ptr<TerrainGenerator> terrainGen;
	std::unique_ptr<Clouds> clouds;
	std::unique_ptr<Sun> sun;
	ChunkManager chunkManager;
	Fog fog;

	std::atomic<bool> isRunning;
	std::mutex mainMutex;

	void loadChunks();
	void renderChunks();
	void renderEntities();
	void addLoadChunksThread();
	void updateDefaultSpawnPoint();
public:
	World(std::shared_ptr<Player>& player, std::shared_ptr<Renderer>& renderer);
	~World();

	const Sun& getSun() { return *sun; }
	const Clouds& getClouds() { return *clouds; }
	TerrainGenerator& getTerrainGenerator() { return *terrainGen; }

	const Fog& getFog();
	int getHeightAt(const glm::vec3& pos);
	void render();
	void updateChunks();
	void update(float deltaTime);
	void updateChunk(const glm::vec3& pos);
	void setBlock(const glm::vec3& pos, Material materialID);
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
	glm::ivec2 getLocalChunkPosition(const glm::vec3& pos);
	std::shared_ptr<Chunk> getChunk(const glm::vec3& pos);
	std::shared_ptr<Block> getBlock(const glm::vec3& pos);
	std::shared_ptr<Block> getHighestBlockAt(const glm::vec3& pos);
};

#endif