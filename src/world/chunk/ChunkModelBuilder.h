#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H

#include "ChunkModel.h"
#include "Chunk.h"

class ChunkModel;
class BlockType;
class Block;

class ChunkModelBuilder {
	std::shared_ptr<ChunkModel> activeMesh;
	ChunkModelCollection* model;
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
	ChunkModelBuilder(Chunk& chunk, ChunkModelCollection& model);

	void build();
};

#endif