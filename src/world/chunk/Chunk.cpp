#include "Chunk.h"

#include "../World.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk(World* world, glm::vec2 pos)
	: world(world), position(pos) {
	for (int i = 0; i < CHUNK_VOL; ++i) {
		blocks[i] = Block(AIR);
	}
	
	makeAABB();
	meshes.setAABB(aabb);
}

void Chunk::makeAABB() {
	glm::vec3 wp1 = getWorldPosition(glm::vec3(0, 0, 0));
	glm::vec3 wp2 = getWorldPosition(glm::vec3(CHUNK_W, CHUNK_H, CHUNK_D));

	aabb = AABB(wp1, wp2);
}

Block& Chunk::getHighestBlockAt(const glm::vec3& pos) {
	return getBlock(glm::vec3(pos.x, getHeightAt(pos), pos.z));
}

int Chunk::getHeightAt(const glm::vec3& pos) {
	return highestBlocks[glm::vec2(pos.x, pos.z)];
}

void Chunk::render(Renderer& renderer) {
	if (hasMesh()) {
		bufferMesh();

		renderer.addChunk(this);
	}
}

void Chunk::makeMesh(Camera& camera) {
	if (!hasMesh()) {
		ChunkMeshBuilder(this).build();

		bHasMesh = true;
		bHasBuffered = false;
	}
}

void Chunk::bufferMesh() {
	if (!hasBuffered()) {
		meshes.createBuffers();

		bHasBuffered = true;
	}
}

void Chunk::resetMeshes() {
	bHasMesh = false;
	bHasBuffered = false;

	meshes.solid->getModel().reset();
	meshes.water->getModel().reset();
}

void Chunk::load(TerrainGenerator& terrainGen) {
	if (bIsLoaded)
		return;

	terrainGen.generateTerrain(this);
	bIsLoaded = true;
}

Block& Chunk::getBlock(const glm::vec3& pos) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H) {
		Block block(AIR);

		return block;
	}

	if (outOfBounds(pos)) {
		glm::vec3 worldPos = getWorldPosition(pos);

		return world->getBlock(worldPos);
	}

	return blocks[toBlockIndex(pos)];
}

void Chunk::setBlock(const glm::vec3& pos, Block block) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H)
		return;

	if (outOfBounds(pos)) {
		glm::vec3 worldPos = getWorldPosition(pos);

		world->setBlock(worldPos, block);
	}

	updateHighestBlock(pos, block);

	blocks[toBlockIndex(pos)] = block;
}

bool Chunk::outOfBounds(const glm::vec3& pos) {
	return pos.x >= CHUNK_W || pos.z >= CHUNK_D
		|| pos.x < 0 || pos.z < 0;
}

glm::vec3 Chunk::getWorldPosition(const glm::vec3& blockPos) {
	return glm::vec3(
		position.x * CHUNK_W + blockPos.x,
		blockPos.y,
		position.y * CHUNK_D + blockPos.z
	);
}

void Chunk::updateHighestBlock(const glm::vec3& pos, Block& block) {
	glm::vec2 posXZ = glm::vec2(pos.x, pos.z);
	float y = pos.y;

	if (highestBlocks.find(posXZ) == highestBlocks.end()) {
		highestBlocks.emplace(posXZ, y);
	}
	else {
		if (!block.type->colliders.size()) {
			if (y == highestBlocks[pos]) {
				Block block = getBlock(glm::vec3(pos.x, y--, pos.z));

				while (!block.type->colliders.size()) {
					block = getBlock(glm::vec3(pos.x, y--, pos.z));
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
	return (pos.y * CHUNK_AREA + pos.z * CHUNK_W + pos.x);
}