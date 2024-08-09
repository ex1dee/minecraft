#include "ChunkManager.h"

#include "../World.h"

ChunkManager::ChunkManager(World* world)
	: world(world) {
	
}

ChunkManager::~ChunkManager() {
	for (std::pair<glm::vec2, Chunk*> pair : chunks) {
		delete pair.second;
	}
}

void ChunkManager::makeMesh(const glm::vec2& pos, Camera& camera) {
	Chunk* chunk = getChunk(pos);

	if (chunk == nullptr || !chunk->hasMesh()) {
		load(pos);

		chunk->makeMesh(camera);
	}
}

Chunk* const ChunkManager::load(const glm::vec2& pos) {
	Chunk* chunk = getChunk(pos);
	if (chunk->isLoaded())
		return chunk;

	chunk->load(world->getTerrainGenerator());
	loadedChunks.emplace(pos, chunk);

	return chunk;
}

void ChunkManager::unload(const glm::vec2& pos) {
	unloadedChunks.insert(pos);
}

Chunk* const ChunkManager::getChunk(const glm::vec2& pos) {
	if (pos.x != pos.x || pos.y != pos.y)
		return nullptr;

	if (!chunkExistsAt(pos)) {
		Chunk* chunk = new Chunk(world, pos);

		chunks.emplace(pos, chunk);
	}

	return chunks[pos];
}

bool ChunkManager::chunkExistsAt(const glm::vec2& pos) {
	return chunks.find(pos) != chunks.end();
}