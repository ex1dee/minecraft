#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include "../block/Block.h"
#include "ChunkMesh.h"
#include "Chunk.h"

class ChunkMeshBuilder {
	ChunkMesh* activeMesh;
	Block* curBlock;
	Chunk* chunk;

	bool shouldAddFace(glm::vec3 adjacentDir, BlockType blockType);
	void tryAddFace(const std::array<float, 12>& vertices,
		const glm::vec2& texCoords,
		const glm::vec3& normal,
		const glm::vec3& localBlockPosition,
		const glm::vec3& adjacentDir,
		const BlockType& blockType);
	void setActiveMesh(Block& block);
public:
	ChunkMeshBuilder(Chunk* chunk);

	void build();
};

#endif