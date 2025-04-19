#ifndef INCL_CHUNK_H
#define INCL_CHUNK_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "../generation/terrain/TerrainGenerator.h"
#include "../../math/shapes/AABB.h"
#include "../../render/Renderer.h"
#include "../block/Block.h"
#include "ChunkModelBuilder.h"
#include "ChunkModel.h"

class World;

class Chunk {
	friend class World;
	friend class ChunkManager;
	friend class ChunkModelBuilder;

	std::unordered_map<glm::ivec2, int> highestBlocks;
	std::array<std::shared_ptr<Block>, CHUNK_VOL> blocks;
	ChunkModelCollection model;
	glm::ivec2 position;
	World* world;
	AABB aabb;

	bool updating = false;
	bool meshed = false;
	bool buffered = false;
	bool loaded = false;

	std::shared_ptr<Block> getHighestBlockAt(const glm::vec3& pos);
	int getHeightAt(const glm::vec3& pos);
	bool outOfBounds(const glm::vec3& pos);
	void makeAABB();
	void makeModel();
	void bufferModel();
	void resetMeshes();
	void load(TerrainGenerator& terrainGen);
	void updateHighestBlock(const glm::vec3& pos, const Block& block);
public:
	Chunk(World& world, glm::ivec2 pos);

	bool isLoaded() { return loaded; }
	bool hasMesh() { return meshed; }
	bool hasBuffered() { return buffered; }
	bool isUpdating() { return updating; }

	ChunkModelCollection& getModel() { return model; }
	glm::ivec2 getLocalPosition() { return position; }
	AABB& getAABB() { return aabb; }

	std::shared_ptr<Block> getBlock(const glm::vec3& pos);
	std::shared_ptr<Block> setBlock(const glm::vec3& pos, Material material);
	glm::vec3 getWorldPosition(const glm::vec3& blockPos);

	static int toBlockIndex(const glm::vec3& pos);
	static glm::vec3 getLocalBlockPosition(int index);
	static glm::vec3 getLocalBlockPosition(const glm::vec3& pos);
};

#endif