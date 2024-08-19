#include "World.h"

#include <GLFW/glfw3.h>

#include "../shaders/ShadersDatabase.h"
#include "../utils/random/Random.h"
#include "../utils/PointerUtils.h"
#include "../config/Config.h"

constexpr float SPAWNPOINT_CHUNKS_RANGE = 100.0f;

World::World(Player &player, Renderer& renderer)
	: player(&player), renderer(&renderer) {
	player.hookWorld(this);
	seed = time(0);

	chunkManager = ChunkManager(*this);
	terrainGen = new DefaultWorldGenerator(seed);

	isRunning = true;

	updateDefaultSpawnPoint();
	addLoadChunksThread();

	sun = new Sun(ShadersDatabase::get(ShaderType::FRAMEBUFFER), *this, player);
	clouds = new Clouds(seed, player, *this);
}

World::~World() {
	isRunning = false;

	for (std::thread& thr : loadThreads) {
		thr.join();
	}

	freePointer(&sun);
	freePointer(&clouds);
	freePointer(&terrainGen);
}

const Fog& World::getFog() {
	Liquid* liquid = player->getLiquidAtEyes();

	if (liquid != nullptr) {
		return liquid->getFog();
	} else {
		//int loadDist = Config::settings["world"]["loadDistance"];
		//fog.zStart = loadDist * CHUNK_D - 20;
		//fog.zEnd = fog.zStart + 20;

		return fog;
	}
}

void World::addLoadChunksThread() {
	loadThreads.push_back(std::thread([&]() { loadChunks(); }));
}

void World::updateDefaultSpawnPoint() {
	glm::vec2 chunkPos{ 0, 0 };
	glm::vec3 blockPos{ 0, 0, 0 };

	int h = terrainGen->getMinSpawnHeight();
	RandomGenerator randGen(seed);
	Chunk* chunk = nullptr;

	while (blockPos.y < h) {
		if (chunk != nullptr)
			chunkManager.unload(chunkPos);

		chunkPos.x = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		chunkPos.y = rangedRand(randGen, -SPAWNPOINT_CHUNKS_RANGE, SPAWNPOINT_CHUNKS_RANGE);
		blockPos.x = rangedRand(randGen, 0, CHUNK_W - 1);
		blockPos.z = rangedRand(randGen, 0, CHUNK_D - 1);

		chunk = chunkManager.load(chunkPos);
		blockPos.y = chunk->getHeightAt(blockPos);
	}

	glm::vec3 spawnPos = chunk->getWorldPosition(blockPos) + glm::vec3(0.5, 1, 0.5);
	player->transform.position = spawnPos;
	spawnPoint = spawnPos;
}

void World::loadChunks() {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		glm::vec2 playerPos = getLocalChunkPosition(player->transform.position);
		int loadDist = Config::settings["world"]["loadDistance"];

		makeMeshes(playerPos, loadDist);
		unloadNotVisibleChunks(playerPos, loadDist);
		deleteUnloadedChunks();
	}
}

void World::makeMeshes(const glm::vec2& chunkPos, int loadDist) {
	for (int i = 0; i <= loadDist; ++i) {
		for (int x = chunkPos.x - i; x <= chunkPos.x + i; ++x) {
			chunkManager.makeMesh(glm::vec2(x, chunkPos.y - i));
		}

		for (int z = chunkPos.y - i + 1; z <= chunkPos.y + i - 1; ++z) {
			chunkManager.makeMesh(glm::vec2(chunkPos.x - i, z));
			chunkManager.makeMesh(glm::vec2(chunkPos.x + i, z));
		}

		for (int x = chunkPos.x - i; x <= chunkPos.x + i; ++x) {
			chunkManager.makeMesh(glm::vec2(x, chunkPos.y + i));
		}
	}
}

void World::unloadNotVisibleChunks(const glm::vec2& chunkPos, int loadDist) {
	for (std::pair<glm::vec2, Chunk*> pair : chunkManager.chunks) {
		Chunk* chunk = pair.second;
		if (chunk == nullptr)
			continue;

		glm::vec2 chunkPos = chunk->getLocalPosition();

		float minX = chunkPos.x - loadDist;
		float maxX = chunkPos.x + loadDist;
		float minZ = chunkPos.y - loadDist;
		float maxZ = chunkPos.y + loadDist;

		if (chunkPos.x < minX || chunkPos.x > maxX || chunkPos.y < minZ || chunkPos.y > maxZ) {
			chunkManager.unload(chunkPos);
		}
	}
}

void World::deleteUnloadedChunks() {
	for (const glm::vec2& chunkPos : chunkManager.unloadedChunks) {
		deleteChunkAt(chunkPos);
	}

	chunkManager.unloadedChunks.clear();
}

void World::deleteChunkAt(const glm::vec2& chunkPos) {
	Chunk* chunk = chunkManager.getChunk(chunkPos);
	chunkManager.loadedChunks.erase(chunkPos);
	chunkManager.chunks.erase(chunkPos);

	freePointer(&chunk);
}

void World::render() {
	renderEntities();
	renderChunks();
}

void World::renderEntities() {
	renderer->addEntity(player);
}

void World::renderChunks() {
	for (std::pair<glm::vec2, Chunk*> pair : chunkManager.loadedChunks) {
		Chunk* chunk = pair.second;
		if (chunk == nullptr)
			continue;

		chunk->render(*renderer);
	}
}

void World::update(float deltaTime) {
	updateChunks();

//	sun->setTime((float)glfwGetTime() * 30.0f);
	clouds->update(deltaTime);
}

void World::updateChunk(const glm::vec3& pos) {
	Chunk* chunk = getChunk(pos);
	chunkUpdates.push_back(chunk);
}

void World::updateChunks() {
	for (Chunk* chunk : chunkUpdates) {
		chunk->resetMeshes();
		std::unique_lock<std::mutex> lock(mainMutex);
		chunk->makeMesh();
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

void World::setBlock(const glm::vec3& pos, Material materialID) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->setBlock(worldPos.localBlockPos, materialID);
}

WorldPosition World::getWorldPosition(const glm::vec3& pos) {
	WorldPosition worldPos;

	worldPos.localBlockPos = getLocalBlockPosition(floor(pos));
	worldPos.chunk = getChunk(pos);

	return worldPos;
}

Chunk* const World::getChunk(const glm::vec3& pos) {
	glm::vec2 locChunkPos = getLocalChunkPosition(pos);
	return chunkManager.getChunk(locChunkPos);
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