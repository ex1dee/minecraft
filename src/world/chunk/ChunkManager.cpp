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
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dz = -1; dz <= 1; ++dz) {
			load(pos + glm::vec2(dx, dz));
		}
	}

	getChunk(pos)->makeMesh(camera);
}

Chunk* ChunkManager::load(const glm::vec2& pos) {
	Chunk* chunk = getChunk(pos);
	chunk->load(world->getTerrainGenerator());
		
	return chunk;
}

void ChunkManager::unload(const glm::vec2& pos) {
	chunks.erase(pos);
}

Chunk* ChunkManager::getChunk(const glm::vec2& pos) {
	if (!chunkExistsAt(pos)) {
		Chunk* chunk = new Chunk(world, pos);

		chunks.emplace(pos, chunk);
	}

	return chunks[pos];
}

bool ChunkManager::chunkExistsAt(const glm::vec2& pos) {
	return chunks.find(pos) != chunks.end();
}