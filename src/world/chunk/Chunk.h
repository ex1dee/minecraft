#ifndef INCL_CHUNK_H
#define INCL_CHUNK_H

#include "../generation/terrain/TerrainGenerator.h"
#include "../../math/shapes/AABB.h"
#include "../../render/Renderer.h"
#include "../../utils/VecMap.h"
#include "../block/Block.h"
#include "ChunkMesh.h"

class World;

class Chunk {
	friend class World;
	friend class ChunkManager;

	std::unordered_map<glm::vec2, int, Vec2Hash> highestBlocks;
	std::array<Block, CHUNK_VOL> blocks;
	ChunkMeshCollection meshes;
	glm::vec2 position;
	World* world;
	AABB aabb;

	bool bHasMesh = false;
	bool buffered = false;
	bool loaded = false;

	Block* getHighestBlockAt(const glm::vec3& pos);
	int getHeightAt(const glm::vec3& pos);
	bool outOfBounds(const glm::vec3& pos);
	void makeAABB();
	void bufferMesh();
	void resetMeshes();
	void makeMesh(Camera& camera);
	void render(Renderer& renderer);
	void load(TerrainGenerator& terrainGen);
	void updateHighestBlock(const glm::vec3& pos, Block& block);
public:
	Chunk() {}
	Chunk(World* world, glm::vec2 pos);

	bool isLoaded() { return loaded; }
	bool hasMesh() { return bHasMesh; }
	bool hasBuffered() { return buffered; }
	Block* getFirstBlock() { return &blocks[0]; }
	ChunkMeshCollection& getMeshes() { return meshes; }
	glm::vec2 getLocalPosition() { return position; }
	AABB& getAABB() { return aabb; }

	Block* getBlock(const glm::vec3& pos);
	void setBlock(const glm::vec3& pos, Block block);
	glm::vec3 getWorldPosition(const glm::vec3& blockPos);

	static glm::vec3 getLocalBlockPosition(int index);
	static int toBlockIndex(const glm::vec3& pos);
};

#endif