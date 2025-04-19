#include "Chunk.h"

#include "../World.h"

Chunk::Chunk(World& world, glm::ivec2 pos)
	: world(&world), position(pos) {
	for (int i = 0; i < CHUNK_VOL; ++i) {
		blocks[i] = std::make_shared<Block>(AIR);
	}

	makeAABB();
	model.setAABB(aabb);
}

void Chunk::makeAABB() {
	glm::vec3 wp1 = getWorldPosition(glm::vec3(0, 0, 0));
	glm::vec3 wp2 = getWorldPosition(glm::vec3(CHUNK_W, CHUNK_H, CHUNK_D));

	aabb = AABB(wp1, wp2);
}

void Chunk::makeModel() {
	if (!hasMesh()) {
		ChunkModelBuilder(*this, this->model).build();

		meshed = true;
		buffered = false;
	}
}

void Chunk::bufferModel() {
	if (hasMesh() && !hasBuffered()) {
		model.createBuffers();

		buffered = true;
	}
}

void Chunk::resetMeshes() {
	meshed = false;
	buffered = false;

	model.reset();
}

void Chunk::load(TerrainGenerator& terrainGen) {
	if (loaded)
		return;

	terrainGen.generateTerrain(this);
	loaded = true;
}


std::shared_ptr<Block> Chunk::getHighestBlockAt(const glm::vec3& pos) {
	return getBlock(glm::vec3(pos.x, getHeightAt(pos), pos.z));
}

int Chunk::getHeightAt(const glm::vec3& pos) {
	return highestBlocks[glm::ivec2(pos.x, pos.z)];
}

std::shared_ptr<Block> Chunk::getBlock(const glm::vec3& pos) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H) {
		return nullptr;
	}

	if (outOfBounds(pos)) {
		glm::vec3 worldPos = getWorldPosition(pos);

		return world->getBlock(worldPos);
	}

	return blocks[toBlockIndex(pos)];
}

std::shared_ptr<Block> Chunk::setBlock(const glm::vec3& pos, Material material) {
	if (pos.y < 0 || ceil(pos.y) >= CHUNK_H)
		return nullptr;

	glm::vec3 worldPos = getWorldPosition(pos);

	std::shared_ptr<Block> block = std::make_shared<Block>(material);
	block->position = worldPos;

	if (outOfBounds(pos)) {
		return world->setBlock(worldPos, material);
	}

	updateHighestBlock(pos, *block);
	blocks[toBlockIndex(pos)] = block;

	return block;
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

void Chunk::updateHighestBlock(const glm::vec3& pos, const Block& block) {
	glm::ivec2 posXZ = glm::ivec2(pos.x, pos.z);
	float y = pos.y;

	if (highestBlocks.find(posXZ) == highestBlocks.end()) {
		highestBlocks.emplace(posXZ, y);
	}
	else {
		if (!block.getType().colliders.size()) {
			if (y == highestBlocks[pos]) {
				std::shared_ptr<Block> blockBelow = getBlock(glm::vec3(pos.x, y--, pos.z));

				while (blockBelow != nullptr && !blockBelow->getType().colliders.size()) {
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

glm::vec3 Chunk::getLocalBlockPosition(const glm::vec3& pos) {
	int x, z;

	x = (int)floor(pos.x) % CHUNK_W;

	if (pos.x < 0) {
		x += CHUNK_W;

		if (x == 16)
			x = 0;
	}

	z = (int)floor(pos.z) % CHUNK_D;

	if (pos.z < 0) {
		z += CHUNK_D;

		if (z == 16)
			z = 0;
	}

	return glm::vec3(x, pos.y, z);
}

int Chunk::toBlockIndex(const glm::vec3& pos) {
	return (floor(pos.y) * CHUNK_AREA + floor(pos.z) * CHUNK_W + floor(pos.x));
}