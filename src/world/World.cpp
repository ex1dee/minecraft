#include "World.h"

#include <GLFW/glfw3.h>

#include "../shaders/ShadersDatabase.h"
#include "../utils/random/Random.h"
#include "../config/Config.h"

constexpr float SPAWNPOINT_CHUNKS_RANGE = 100.0f;

World::World(std::shared_ptr<Player>& player, std::shared_ptr<Renderer>& renderer)
	: player(player), renderer(renderer) {
	player->hookWorld(this);
	seed = time(0);

	chunkManager = ChunkManager(*this);
	terrainGen = std::make_unique<DefaultWorldGenerator>(seed);

	isRunning = true;

	updateDefaultSpawnPoint();
	addLoadChunksThread();
	
	sun = std::make_unique<Sun>(ShadersDatabase::get(ShaderType::FRAMEBUFFER), *this, this->player);
	clouds = std::make_unique<Clouds>(seed, player, *this);
}

World::~World() {
	isRunning = false;

	for (std::thread& thr : loadThreads) {
		thr.join();
	}
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
	glm::ivec2 chunkPos{ 0, 0 };
	glm::vec3 blockPos{ 0, 0, 0 };

	int h = terrainGen->getMinSpawnHeight();
	RandomGenerator randGen(seed);
	std::shared_ptr<Chunk> chunk;

	while (blockPos.y < h) {
		if (chunk != nullptr)
			chunkManager.markAsUnloadedChunk(chunkPos);

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

		glm::ivec2 playerPos = getLocalChunkPosition(player->transform.position);
		int loadDist = Config::settings["world"]["loadDistance"];
		
		chunkManager.makeMeshes(playerPos, loadDist);
		chunkManager.unloadNotVisibleChunks(playerPos, loadDist);
		chunkManager.deleteUnloadedChunks();
	}
}

void World::render() {
	renderEntities();
	renderChunks();
}

void World::renderEntities() {
	renderer->addEntity(*player);
}

void World::renderChunks() {
	for (auto& pair : chunkManager.loadedChunks) {
		Chunk* chunk = pair.second.get();
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
	std::shared_ptr<Chunk> chunk = getChunk(pos);
	chunkUpdates.push_back(std::move(chunk));
}

void World::updateChunks() {
	for (auto& chunk : chunkUpdates) {
		chunk->resetMeshes();
		chunk->makeMesh();
	}

	chunkUpdates.clear();
}

int World::getHeightAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	return worldPos.chunk->getHeightAt(worldPos.localBlockPos);
}

std::shared_ptr<Block> World::getHighestBlockAt(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	if (worldPos.chunk == nullptr)
		return nullptr;

	return worldPos.chunk->getHighestBlockAt(worldPos.localBlockPos);
}

std::shared_ptr<Block> World::getBlock(const glm::vec3& pos) {
	WorldPosition worldPos = getWorldPosition(pos);
	if (worldPos.chunk == nullptr || !worldPos.chunk->isLoaded())
		return nullptr;

	return worldPos.chunk->getBlock(worldPos.localBlockPos);
}

void World::setBlock(const glm::vec3& pos, Material materialID) {
	WorldPosition worldPos = getWorldPosition(pos);
	if (worldPos.chunk == nullptr || !worldPos.chunk->isLoaded())
		return;

	return worldPos.chunk->setBlock(worldPos.localBlockPos, materialID);
}

WorldPosition World::getWorldPosition(const glm::vec3& pos) {
	WorldPosition worldPos;

	worldPos.localBlockPos = getLocalBlockPosition(floor(pos));
	worldPos.chunk = getChunk(pos);

	return worldPos;
}

std::shared_ptr<Chunk> World::getChunk(const glm::vec3& pos) {
	glm::ivec2 locChunkPos = getLocalChunkPosition(pos);
	return chunkManager.getChunk(locChunkPos);
}

glm::ivec2 World::getLocalChunkPosition(const glm::vec3& pos) {
	return glm::ivec2(floor(pos.x / CHUNK_W), floor(pos.z / CHUNK_D));
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