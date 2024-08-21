#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include "ChunkMesh.h"
#include "Chunk.h"

class ChunkMesh;
class BlockType;
class Block;

class ChunkMeshBuilder {
	std::shared_ptr<ChunkMesh> activeMesh;
	Chunk* chunk;

	bool shouldAddFace(glm::vec3 adjacentDir, const BlockType& blockType);
	void addCube(const glm::vec3& blockPos, const BlockType& blockType);
	void addX(const glm::vec3& blockPos, const BlockType& blockType);
	void tryAddFace(const std::array<float, 12>& vertices,
		const glm::vec2& texCoords,
		const glm::vec3& normal,
		const glm::vec3& localBlockPosition,
		const glm::vec3& adjacentDir,
		const BlockType& blockType);
	void setActiveMesh(const BlockType& blockType);
public:
	ChunkMeshBuilder(Chunk& chunk);

	void build();
};

#endif