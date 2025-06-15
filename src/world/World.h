#ifndef WORLD_H
#define WORLD_H

#include <unordered_set>
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
	std::unordered_set<glm::ivec2> chunkUpdates;
	std::vector<std::thread> loadThreads;
	std::vector<std::thread> updateThreads;
	std::vector<std::shared_ptr<Entity>> entities;

	glm::vec3 spawnPoint;
	uint32_t seed;
	int time;

	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Player> player;

	std::unique_ptr<TerrainGenerator> terrainGen;
	std::unique_ptr<Clouds> clouds;
	std::unique_ptr<Sun> sun;
	ChunkManager chunkManager;
	Fog fog;

	std::atomic<bool> isRunning;

	void updateTime();
	void loadChunks();
	void updateChunks();
	void renderChunks();
	void renderEntities();
	void addLoadChunksThreads();
	void addUpdateChunksThread();
	void updateDefaultSpawnPoint();
	void updateEntities(float deltaTime);
public:
	World(std::shared_ptr<Player>& player, std::shared_ptr<Renderer>& renderer);
	~World();

	const Sun& getSun() { return *sun; }
	const Clouds& getClouds() { return *clouds; }
	TerrainGenerator& getTerrainGenerator() { return *terrainGen; }

	void render();
	void playAnimations(float deltaTime);
	void update(float deltaTime);
	void updateChunk(const glm::vec3& pos);
	void despawnEntity(const Entity& entity);
	int getHeightAt(const glm::vec3& pos);
	const Fog& getFogForEntity(const Entity& entity);
	WorldPosition getWorldPosition(const glm::vec3& pos);
	glm::ivec2 getLocalChunkPosition(const glm::vec3& pos);
	std::shared_ptr<Chunk> getChunk(const glm::vec3& pos);
	std::shared_ptr<Block> getBlock(const glm::vec3& pos);
	std::shared_ptr<Block> getHighestBlockAt(const glm::vec3& pos);
	std::shared_ptr<Block> setBlock(const glm::vec3& pos, Material material);

	template<typename T, typename... Ts, typename = typename std::enable_if_t<std::is_base_of_v<Entity, T>>>
		std::shared_ptr<T> spawnCameraSpaceEntity(const glm::vec3& pos, Ts&&... args);
	template<typename T, typename... Ts, typename = typename std::enable_if_t<std::is_base_of_v<Entity, T>>>
		std::shared_ptr<T> spawnEntity(const glm::vec3& pos, Ts&&... args);
	template<typename T> std::vector<std::shared_ptr<T>> getEntitiesNearTo(const glm::vec3& position, float radius);
};

#include "World.inl"

#endif