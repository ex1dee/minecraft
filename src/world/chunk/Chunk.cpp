#include "Chunk.h"

#include "../World.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk(World* world, glm::vec2 pos)
	: world(world), position(pos) {
	for (int i = 0; i < CHUNK_VOL; ++i) {
		blocks[i] = new Block(AIR);
	}
	
	makeAABB();
	meshes.setAABB(aabb);
}

void Chunk::makeAABB() {
	glm::vec3 wp1 = getWorldPosition(glm::vec3(0, 0, 0));
	glm::vec3 wp2 = getWorldPosition(glm::vec3(CHUNK_W, CHUNK_H, CHUNK_D));

	aabb = AABB(wp1, wp2);
}

void Chunk::render(Renderer& renderer) {
	if (hasMesh()) {
		bufferMesh();

		renderer.addChunk(this);
	}
}

void Chunk::makeMesh() {
	if (!hasMesh()) {
		ChunkMeshBuilder(this).build();

		bHasMesh = true;
		buffered = false;
	}
}

void Chunk::bufferMesh() {
	if (!hasBuffered()) {
		meshes.createBuffers();

		buffered = true;
	}
}

void Chunk::resetMeshes() {
	bHasMesh = false;
	buffered = false;

	meshes.solid->getModel().reset();
	meshes.water->getModel().reset();
}

void Chunk::load(TerrainGenerator& terrainGen) {
	if (loaded)
		return;

	terrainGen.generateTerrain(this);
	loaded = true;
}


Block* Chunk::getHighestBlockAt(const glm::vec3& pos) {
	return getBlock(glm::vec3(pos.x, getHeightAt(pos), pos.z));
}

int Chunk::getHeightAt(const glm::vec3& pos) {
	return highestBlocks[glm::vec2(pos.x, pos.z)];
}

Block* Chunk::getBlock(const glm::vec3& pos) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H) {
		return nullptr;
	}

	if (outOfBounds(pos)) {
		glm::vec3 worldPos = getWorldPosition(pos);

		return world->getBlock(worldPos);
	}

	return blocks[toBlockIndex(pos)];
}

void Chunk::setBlock(const glm::vec3& pos, BlockID blockID) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H)
		return;

	glm::vec3 worldPos = getWorldPosition(pos);

	Block* block = new Block(blockID);
	block->position = worldPos;

	if (outOfBounds(pos)) {
		world->setBlock(worldPos, blockID);

		return;
	}

	updateHighestBlock(pos, block);

	int blockIndex = toBlockIndex(pos);

	delete blocks[blockIndex];
	blocks[blockIndex] = block;
}

bool Chunk::outOfBounds(const glm::vec3& pos) {
	return pos.x >= CHUNK_W || pos.z >= CHUNK_D
		|| pos.x < 0 || pos.z < 0;
}

glm::vec3 Chunk::getWorldPosition(const glm::vec3& blockPos) {
	return glm::vec3(
		position.x * CHUNK_W + floor(blockPos.x),
		floor(blockPos.y),
		position.y * CHUNK_D + floor(blockPos.z)
	);
}

void Chunk::updateHighestBlock(const glm::vec3& pos, Block* block) {
	glm::vec2 posXZ = glm::vec2(pos.x, pos.z);
	float y = pos.y;

	if (highestBlocks.find(posXZ) == highestBlocks.end()) {
		highestBlocks.emplace(posXZ, y);
	}
	else {
		if (!block->type->colliders.size()) {
			if (y == highestBlocks[pos]) {
				Block* blockBelow = getBlock(glm::vec3(pos.x, y--, pos.z));

				while (blockBelow != nullptr && !blockBelow->type->colliders.size()) {
					blockBelow = getBlock(glm::vec3(pos.x, y--, pos.z));
				}
			}
		} else {
			if (y > highestBlocks[posXZ]) {
				highestBlocks[posXZ] = y;
			}
		}
	}
}

glm::vec3 Chunk::getLocalBlockPosition(int index) {
	glm::vec3 pos;

	pos.x = index % CHUNK_W;
	pos.y = index / CHUNK_AREA;
	pos.z = (index / CHUNK_D) % CHUNK_D;
	
	return pos;
}

int Chunk::toBlockIndex(const glm::vec3& pos) {
	return (floor(pos.y) * CHUNK_AREA + floor(pos.z) * CHUNK_W + floor(pos.x));
}