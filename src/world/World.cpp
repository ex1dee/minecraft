#include "World.h"

#include <GLFW/glfw3.h>

#include "../config/Config.h"
#include "../utils/random/Random.h"
#include "../shaders/ShadersDatabase.h"

World::World(TerrainGenerator* terrainGen, Player &player, Camera& camera)
	: terrainGen(terrainGen) {
	chunkManager = new ChunkManager(this);
	isRunning = true;
	seed = time(0);

	player.hookWorld(this);

	makeSun();
	updateDefaultSpawnPoint(player);
	addLoadChunksThread(player, camera);
}

World::~World() {
	isRunning = false;

	for (std::thread& thr : loadThreads) {
		thr.join();
	}

	delete sun;
	delete chunkManager;
	delete terrainGen;
}

void World::makeSun() {
	sun = new Sun(ShadersDatabase::get(FRAMEBUFFER), this);
}

void World::addLoadChunksThread(Player& player, Camera& camera) {
	loadThreads.push_back(std::thread([&]() { loadChunks(player, camera); }));
}

void World::updateDefaultSpawnPoint(Player& player) {
	glm::vec2 chunkPos{ 0, 0 };
	glm::vec3 blockPos{ 0, 0, 0 };

	RandomGenerator randGen(seed);
	Chunk* chunk = chunkManager->getChunk(chunkPos);
	int h = terrainGen->getMinSpawnHeight();

	while (blockPos.y < h) {
		chunkManager->unload(chunkPos);

		chunkPos.x = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		chunkPos.y = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		blockPos.x = rangedRand(randGen, 0, CHUNK_W - 1);
		blockPos.z = rangedRand(randGen, 0, CHUNK_D - 1);

		chunk = chunkManager->load(chunkPos);
		blockPos.y = chunk->getHeightAt(blockPos);
	}

	glm::vec3 spawnPos = chunk->getWorldPosition(blockPos) + glm::vec3(0, 1, 0);
	player.transform.position = spawnPos;
	spawnPoint = spawnPos;
}

void World::loadChunks(Player& player, Camera& camera) {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		glm::vec2 playerPos = getLocalChunkPosition(player.transform.position);
		int loadDist = Config::settings["world"]["loadDistance"] - 1;

		std::unique_lock<std::mutex> mainLock(mainMutex, std::defer_lock);

		for (int i = 0; i <= loadDist; ++i) {
			for (int x = playerPos.x - i; x <= playerPos.x + i; ++x) {
				for (int z = playerPos.y - i; z <= playerPos.y + i; ++z) {
					mainLock.lock();
					chunkManager->makeMesh(glm::vec2(x, z), camera);
					mainLock.unlock();
				}
			}
		}

		for (std::pair<glm::vec2, Chunk*> pair : chunkManager->loadedChunks) {
			Chunk* chunk = pair.second;
			if (chunk == nullptr)
				continue;

			glm::vec2 chunkPos = chunk->getLocalPosition();

			float minX = playerPos.x - loadDist;
			float maxX = playerPos.x + loadDist;
			float minZ = playerPos.y - loadDist;
			float maxZ = playerPos.y + loadDist;

			if (chunkPos.x < minX || chunkPos.x > maxX || chunkPos.y < minZ || chunkPos.y > maxZ) { 
				mainLock.lock();
				chunkManager->unload(chunkPos);
				mainLock.unlock();
			}
		}

		for (const glm::vec2& chunkPos : chunkManager->unloadedChunks) {
			mainLock.lock();
			Chunk* chunk = chunkManager->getChunk(chunkPos);
			chunkManager->loadedChunks.erase(chunkPos);
			chunkManager->chunks.erase(chunkPos);
			mainLock.unlock();

			delete chunk;
		}

		chunkManager->unloadedChunks.clear();
	}
}

void World::render(Renderer& renderer, Player& player) {
	renderEntities(renderer, player);
	renderChunks(renderer, player);
}

void World::renderEntities(Renderer& renderer, Player& player) {
	renderer.addEntity(&player);
}

void World::renderChunks(Renderer& renderer, Player& player) {
	for (std::pair<glm::vec2, Chunk*> pair : chunkManager->loadedChunks) {
		Chunk* chunk = pair.second;
		if (chunk == nullptr)
			continue;

		chunk->render(renderer);
	}
}

void World::update(Renderer& renderer, Player& player, Camera& camera) {
	updateChunks(camera);

	sun->setTime((float)glfwGetTime() * 30.0f, player);
}

void World::updateChunk(const glm::vec3& pos) {
	Chunk* chunk = getChunk(pos);
	chunkUpdates.push_back(chunk);
}

void World::updateChunks(Camera& camera) {
	for (Chunk* chunk : chunkUpdates) {
		chunk->resetMeshes();
		std::unique_lock<std::mutex> lock(mainMutex);
		chunk->makeMesh(camera);
	}

	chunkUpdates.clear();
}

int World::getHeightAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->getHeightAt(worldPos.localBlockPos);
}

Block* World::getHighestBlockAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	if (worldPos.chunk == nullptr)
		return nullptr;

	return worldPos.chunk->getHighestBlockAt(worldPos.localBlockPos);
}

Block* World::getBlock(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	if (worldPos.chunk == nullptr)
		return nullptr;

	return worldPos.chunk->getBlock(worldPos.localBlockPos);
}

void World::setBlock(const glm::vec3& pos, Block block) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->setBlock(worldPos.localBlockPos, block);
}

WorldPosition World::getWorldPosition(const glm::vec3& pos) {
	WorldPosition worldPos;
	worldPos.localBlockPos = getLocalBlockPosition(floor(pos));
	worldPos.chunk = getChunk(pos);

	return worldPos;
}

Chunk* const World::getChunk(const glm::vec3& pos) {
	glm::vec2 locChunkPos = getLocalChunkPosition(pos);
	return chunkManager->getChunk(locChunkPos);
}

glm::vec2 World::getLocalChunkPosition(const glm::vec3& pos) {
	return glm::vec2(floor(pos.x / CHUNK_W), floor(pos.z / CHUNK_D));
}

glm::vec3 World::getLocalBlockPosition(const glm::vec3& pos) {
	int x, z;

	if (pos.x >= 0) {
		x = (int)ceil(pos.x) % CHUNK_W;
	} else {
		x = CHUNK_W + (int)floor(pos.x) % CHUNK_W;

		if (x == 16)
			x = 0;
	}

	if (pos.z >= 0) {
		z = (int)ceil(pos.z) % CHUNK_D;
	} else {
		z = CHUNK_D + (int)floor(pos.z) % CHUNK_D;

		if (z == 16)
			z = 0;
	}

	return glm::vec3(x, pos.y, z);
}