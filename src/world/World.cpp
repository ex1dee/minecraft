#include "World.h"

#include <GLFW/glfw3.h>

#include "../shaders/ShadersDatabase.h"
#include "../utils/random/Random.h"
#include "../config/Config.h"

constexpr float SPAWNPOINT_CHUNKS_RANGE = 100.0f;

World::World(std::shared_ptr<Player>& player, std::shared_ptr<Renderer>& renderer)
	: player(player), renderer(renderer) {
	player->hookWorld(this);

	chunkManager = ChunkManager(*this);
	terrainGen = std::make_unique<DefaultWorldGenerator>(seed);

	time = TICK_PER_DAY / 4;
	seed = std::time(0);
	isRunning = true;

	updateDefaultSpawnPoint();
	addUpdateChunksThread();
	addLoadChunksThreads();
	
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

void World::addLoadChunksThreads() {
	loadThreads.push_back(std::thread(&World::loadChunks, this));
}

void World::addUpdateChunksThread() {
	updateThreads.push_back(std::thread(&World::updateChunks, this));
}

void World::loadChunks() {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		glm::ivec2 playerPos = getLocalChunkPosition(player->transform.position);
		int loadDist = Config::settings["world"]["loadDistance"];
		
		chunkManager.deleteNullChunks();
		chunkManager.makeMeshes(playerPos, loadDist);
		chunkManager.unloadNotVisibleChunks(playerPos, loadDist);
		chunkManager.deleteUnloadedChunks();
	}
}

void World::updateChunks() {
	while (isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		for (auto& chunkPos : chunkUpdates) {
			chunkManager.updateChunk(chunkPos);
		}

		chunkUpdates.clear();
	}
}

void World::render() {
	renderEntities();
	renderChunks();
}

void World::renderEntities() {
	std::shared_ptr<Entity> playerEntity = std::dynamic_pointer_cast<Entity>(player);
	renderer->addEntity(playerEntity);

	for (auto& entity : entities) {
		renderer->addEntity(entity);
	}
}

void World::renderChunks() {
	for (auto& pair : chunkManager.visibleChunks) {
		std::shared_ptr<Chunk> chunk = pair.second;
		if (chunk == nullptr)
			continue;

		chunk->bufferModel();
		renderer->addChunk(chunk);
	}
}

void World::playAnimations(float deltaTime) {
	for (auto& entity : entities) {
		if (entity != nullptr)
			entity->playAnimation(player, deltaTime);
	}
}

void World::update(float deltaTime) {
	updateTime();
	updateEntities(deltaTime);

	sun->setTime(time);
	clouds->update(deltaTime);
}

void World::updateTime() {
	if (++time >= TICK_PER_DAY) {
		time = 0;
	}
}

void World::updateEntities(float deltaTime) {
	entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());

	for (auto& entity : entities) {
		if (entity != nullptr && entity->needUpdate())
			entity->update(player, deltaTime);
	}
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

std::shared_ptr<Block> World::setBlock(const glm::vec3& pos, Material material) {
	WorldPosition worldPos = getWorldPosition(pos);

	if (worldPos.chunk == nullptr || !worldPos.chunk->isLoaded())
		return nullptr;
	
	std::shared_ptr<Block> block = worldPos.chunk->setBlock(worldPos.localBlockPos, material);

	if (!worldPos.chunk->hasMesh())
		return nullptr;
 
	if (worldPos.chunk.get() != getChunk(pos + glm::vec3(1, 0, 0)).get())
		updateChunk(pos + glm::vec3(1, 0, 0));
	if (worldPos.chunk.get() != getChunk(pos + glm::vec3(-1, 0, 0)).get())
		updateChunk(pos + glm::vec3(-1, 0, 0));
	if (worldPos.chunk.get() != getChunk(pos + glm::vec3(0, 0, 1)).get())
		updateChunk(pos + glm::vec3(0, 0, 1));
	if (worldPos.chunk.get() != getChunk(pos + glm::vec3(0, 0, -1)).get())
		updateChunk(pos + glm::vec3(0, 0, -1));

	updateChunk(pos);

	return block;
}

void World::updateChunk(const glm::vec3& pos) {
	chunkUpdates.insert(getLocalChunkPosition(pos));
}

WorldPosition World::getWorldPosition(const glm::vec3& pos) {
	WorldPosition worldPos;

	worldPos.chunk = getChunk(pos);
	worldPos.localBlockPos = Chunk::getLocalBlockPosition(pos);

	return worldPos;
}

std::shared_ptr<Chunk> World::getChunk(const glm::vec3& pos) {
	glm::ivec2 locChunkPos = getLocalChunkPosition(pos);
	return chunkManager.getChunk(locChunkPos);
}

glm::ivec2 World::getLocalChunkPosition(const glm::vec3& pos) {
	return glm::ivec2(floor(pos.x / CHUNK_W), floor(pos.z / CHUNK_D));
}

void World::despawnEntity(const Entity& entity) {
	PhysicsEngine::removeObject(entity);

	entities.erase(std::remove_if(entities.begin(), entities.end(), [&](const auto& other) {
		return entity == *other;
	}), entities.end());
}