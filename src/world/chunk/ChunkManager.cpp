#include "ChunkManager.h"

#include "../World.h"

ChunkManager::ChunkManager(World& world)
	: world(&world) {
	
}

void ChunkManager::makeMeshes(const glm::ivec2& playerChunkPos, int loadDist) {
	for (int i = 0; i <= loadDist; ++i) {
		for (int x = playerChunkPos.x - i; x <= playerChunkPos.x + i; ++x) {
			makeModel(glm::ivec2(x, playerChunkPos.y - i));
		}

		for (int z = playerChunkPos.y - i + 1; z <= playerChunkPos.y + i - 1; ++z) {
			makeModel(glm::ivec2(playerChunkPos.x - i, z));
			makeModel(glm::ivec2(playerChunkPos.x + i, z));
		}

		for (int x = playerChunkPos.x - i; x <= playerChunkPos.x + i; ++x) {
			makeModel(glm::ivec2(x, playerChunkPos.y + i));
		}
	}
}

void ChunkManager::makeModel(const glm::ivec2& pos) {
	std::shared_ptr<Chunk> chunk = getChunk(pos);

	if (chunk == nullptr || !chunk->hasMesh()) {
		load(pos + glm::ivec2(1, 0));
		load(pos + glm::ivec2(-1, 0));
		load(pos + glm::ivec2(0, 1));
		load(pos + glm::ivec2(0, -1));

		std::shared_ptr<Chunk> chunk = load(pos);

		if (!chunk->isUpdating())
			chunk->makeModel();
	}
}

std::shared_ptr<Chunk> ChunkManager::load(const glm::ivec2& pos) {
	std::shared_ptr<Chunk> chunk = getChunk(pos);

	if (chunk != nullptr) {
		if (chunk->isLoaded())
			return chunk;
	} else {
		chunks.emplace(pos, std::make_shared<Chunk>(*world, pos));
		chunk = getChunk(pos);
	}

	chunk->load(world->getTerrainGenerator());
	visibleChunks.emplace(pos, chunk);

	return chunk;
}

void ChunkManager::resetChunkMeshes(const glm::ivec2& pos) {
	getChunk(pos)->resetMeshes();
}

void ChunkManager::updateChunk(const glm::ivec2& pos) {
	std::shared_ptr<Chunk> chunk = getChunk(pos);

	if (!chunk->isLoaded())
		return;

	chunk->updating = true;

	ChunkModelCollection newModel;
	ChunkModelBuilder(*chunk, newModel).build();
	chunk->model = newModel;
	chunk->meshed = true;
	chunk->buffered = false;

	chunk->updating = false;
}

std::shared_ptr<Chunk> ChunkManager::getChunk(const glm::ivec2& pos) {
	if (!chunkExistsAt(pos) || chunks[pos] == nullptr)
		return nullptr;

	return chunks[pos];
}

bool ChunkManager::chunkExistsAt(const glm::ivec2& pos) {
	return chunks.contains(pos);
}

void ChunkManager::unloadNotVisibleChunks(const glm::ivec2& playerChunkPos, int loadDist) {
	for (auto pair : chunks) {
		std::shared_ptr<Chunk> chunk = pair.second;
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
		deleteChunk(chunkPos);
	}

	unloadedChunks.clear();
}

void ChunkManager::deleteChunk(const glm::ivec2& chunkPos) {
	visibleChunks.erase(chunkPos);
	chunks.erase(chunkPos);
}

void ChunkManager::deleteNullChunks() {
	std::erase_if(visibleChunks, [](const auto& pair) {
		return pair.second == nullptr;
	});

	std::erase_if(chunks, [](const auto& pair) {
		return pair.second == nullptr;
	});
}