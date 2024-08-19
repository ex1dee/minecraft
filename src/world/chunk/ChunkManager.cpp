#include "ChunkManager.h"

#include "../World.h"

ChunkManager::ChunkManager(World& world)
	: world(&world) {
	
}

ChunkManager::~ChunkManager() {
	freeMapValues(chunks);
}

void ChunkManager::makeMesh(const glm::vec2& pos) {
	Chunk* chunk = getChunk(pos);

	if (chunk == nullptr || !chunk->hasMesh()) {
		load(pos + glm::vec2(1, 0));
		load(pos + glm::vec2(-1, 0));
		load(pos + glm::vec2(0, 1));
		load(pos + glm::vec2(0, -1));
		load(pos);

		chunk->makeMesh();
	}
}

Chunk* const ChunkManager::load(const glm::vec2& pos) {
	Chunk* chunk = getChunk(pos);
	if (chunk != nullptr && chunk->isLoaded())
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
		Chunk* chunk = new Chunk(*world, pos);

		chunks.emplace(pos, chunk);
	}

	return chunks[pos];
}

bool ChunkManager::chunkExistsAt(const glm::vec2& pos) {
	return chunks.find(pos) != chunks.end();
}