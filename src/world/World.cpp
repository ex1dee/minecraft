#include "World.h"

#include "../config/Config.h"
#include "../utils/random/Random.h"

World::World(TerrainGenerator* terrainGen, Player &player, Camera& camera)
	: terrainGen(terrainGen) {
	chunkManager = new ChunkManager(this);
	isRunning = true;
	seed = time(0);

	setSpawnPoint(player);
	loadThreads.push_back(std::thread([&]() { loadChunks(player, camera); }));
}

World::~World() {
	isRunning = false;

	for (std::thread& thr : loadThreads) {
		thr.join();
	}

	delete chunkManager;
	delete terrainGen;
}

void World::setSpawnPoint(Player& player) {
	glm::vec2 chunkPos{ 0, 0 };
	glm::vec3 blockPos{ 0, 0, 0 };

	RandomGenerator randGen(seed);
	Chunk* chunk = chunkManager->getChunk(chunkPos);
	int h = terrainGen->getMinSpawnHeight();

	while (blockPos.y < h) {
		chunkManager->unload(chunkPos);

		chunkPos.x = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		chunkPos.y = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		blockPos.x = rangedRand(randGen, 0, 15);
		blockPos.z = rangedRand(randGen, 0, 15);

		chunk = chunkManager->load(chunkPos);
		blockPos.y = chunk->getHeightAt(blockPos);
	}

	glm::vec3 spawnPos = chunk->toWorldPosition(blockPos) + glm::vec3(0, 1, 0);
	player.transform->position = spawnPos;
	spawnPoint = spawnPos;
}

void World::loadChunks(Player& player, Camera& camera) {
	while (isRunning) {
		glm::vec2 playerPos = getChunkPosition(player.transform->position);
		int loadDist = Config::settings["world"]["loadDistance"] - 1;

		for (int i = 0; i <= loadDist; ++i) {
			for (int x = playerPos.x - i; x <= playerPos.x + i; ++x) {
				for (int z = playerPos.y - i; z <= playerPos.y + i; ++z) {
					std::unique_lock<std::mutex> lock(mainMutex);
					chunkManager->makeMesh(glm::vec2(x, z), camera);
				}
			}
		}
	}
}

void World::render(Renderer& renderer, Camera& camera) {
	glm::vec2 cameraPos = getChunkPosition(camera.transform->position);
	int loadDist = Config::settings["world"]["loadDistance"] - 1;

	for (std::pair<glm::vec2, Chunk*> pair : chunkManager->chunks) {
		Chunk* chunk = pair.second;
		glm::vec2 chunkPos = chunk->getLocalPosition();

		float minX = cameraPos.x - loadDist;
		float maxX = cameraPos.x + loadDist;
		float minZ = cameraPos.y - loadDist;
		float maxZ = cameraPos.y + loadDist;

		if (chunkPos.x >= minX && chunkPos.x <= maxX && chunkPos.y >= minZ && chunkPos.y <= maxZ) {
			if (camera.isAABBInFrustum(chunk->getAABB())) {
				if (chunk->hasMesh())
					chunk->render(renderer);
			}
		}
	}
}

void World::update(Renderer& renderer, Player& player, Camera& camera) {
	updateChunks(camera);

	renderer.setTime(glfwGetTime() * 10);
}

void World::updateChunks(Camera& camera) {
	for (Chunk* chunk : chunkUpdates) {
		chunk->resetMeshes();
		std::unique_lock<std::mutex> lock(mainMutex);
		chunk->makeMesh(camera);
	}

	chunkUpdates.clear();
}

void World::updateChunk(const glm::vec3& pos) {
	glm::vec2 chunkPos = getChunkPosition(pos);
	Chunk* chunk = chunkManager->getChunk(chunkPos);

	chunkUpdates.push_back(chunk);
}

TerrainGenerator& World::getTerrainGenerator() {
	return *terrainGen;
}

int World::getHeightAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->getHeightAt(worldPos.localBlockPos);
}

Block& World::getHighestBlockAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->getHighestBlockAt(worldPos.localBlockPos);
}

Block& World::getBlock(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->getBlock(worldPos.localBlockPos);
}

void World::setBlock(const glm::vec3& pos, Block block) {
	WorldPosition worldPos = getWorldPosition(pos);

	return worldPos.chunk->setBlock(worldPos.localBlockPos, block);
}

WorldPosition World::getWorldPosition(const glm::vec3& pos) {
	glm::vec2 chunkPos = getChunkPosition(pos);
	glm::vec3 locBlockPos = getLocalBlockPosition(pos);

	WorldPosition worldPos;
	worldPos.localBlockPos = locBlockPos;
	worldPos.chunk = chunkManager->getChunk(chunkPos);

	return worldPos;
}

glm::vec2 World::getChunkPosition(const glm::vec3& pos) {
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