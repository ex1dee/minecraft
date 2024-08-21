#include "ChunkManager.h"

#include "../World.h"

ChunkManager::ChunkManager(World& world)
	: world(&world) {
	
}

void ChunkManager::makeMeshes(const glm::ivec2& playerChunkPos, int loadDist) {
	for (int i = 0; i <= loadDist; ++i) {
		for (int x = playerChunkPos.x - i; x <= playerChunkPos.x + i; ++x) {
			makeMesh(glm::ivec2(x, playerChunkPos.y - i));
		}

		for (int z = playerChunkPos.y - i + 1; z <= playerChunkPos.y + i - 1; ++z) {
			makeMesh(glm::ivec2(playerChunkPos.x - i, z));
			makeMesh(glm::ivec2(playerChunkPos.x + i, z));
		}

		for (int x = playerChunkPos.x - i; x <= playerChunkPos.x + i; ++x) {
			makeMesh(glm::ivec2(x, playerChunkPos.y + i));
		}
	}
}

void ChunkManager::makeMesh(const glm::ivec2& pos) {
	std::shared_ptr<Chunk> chunk = getChunk(pos);

	if (chunk == nullptr || !chunk->hasMesh()) {
		load(pos + glm::ivec2(1, 0));
		load(pos + glm::ivec2(-1, 0));
		load(pos + glm::ivec2(0, 1));
		load(pos + glm::ivec2(0, -1));
		load(pos);

		chunk->makeMesh();
	}
}

std::shared_ptr<Chunk> ChunkManager::load(const glm::ivec2& pos) {
	std::shared_ptr<Chunk> chunk = getChunk(pos);
	if (chunk != nullptr && chunk->isLoaded())
		return chunk;

	chunk->load(world->getTerrainGenerator());
	loadedChunks.emplace(pos, chunk);

	return chunk;
}

void ChunkManager::unloadNotVisibleChunks(const glm::ivec2& playerChunkPos, int loadDist) {
	for (auto pair : chunks) {
		std::shared_ptr<Chunk> chunk = pair.second;
		if (chunk == nullptr)
			continue;

		glm::ivec2 chunkPos = chunk->getLocalPosition();

		float minX = playerChunkPos.x - loadDist;
		float maxX = playerChunkPos.x + loadDist;
		float minZ = playerChunkPos.y - loadDist;
		float maxZ = playerChunkPos.y + loadDist;

		if (chunkPos.x < minX || chunkPos.x > maxX || chunkPos.y < minZ || chunkPos.y > maxZ) {
			markAsUnloadedChunk(chunkPos);
		}
	}
}

void ChunkManager::markAsUnloadedChunk(const glm::ivec2& pos) {
	unloadedChunks.insert(pos);
}

void ChunkManager::deleteUnloadedChunks() {
	for (const glm::ivec2& chunkPos : unloadedChunks) {
		deleteChunkAt(chunkPos);
	}

	unloadedChunks.clear();
}

void ChunkManager::deleteChunkAt(const glm::ivec2& chunkPos) {
	std::shared_ptr<Chunk> chunk = std::move(chunks[chunkPos]);

	loadedChunks.erase(chunkPos);
	chunks.erase(chunkPos);

	chunk.reset();
}

std::shared_ptr<Chunk> ChunkManager::getChunk(const glm::ivec2& pos) {
	if (pos.x != pos.x || pos.y != pos.y)
		return nullptr;

	if (!chunkExistsAt(pos)) {
		chunks.try_emplace(pos, std::make_shared<Chunk>(*world, pos));
	}

	return chunks[pos];
}

bool ChunkManager::chunkExistsAt(const glm::ivec2& pos) {
	return chunks.find(pos) != chunks.end();
}