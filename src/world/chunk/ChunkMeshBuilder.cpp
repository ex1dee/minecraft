#include "ChunkMeshBuilder.h"

#include "../block/BlockFaces.h"
#include "../block/BlockType.h"

const std::array<float, 12> frontFace{
	0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
};

const std::array<float, 12> backFace{
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
};

const std::array<float, 12> leftFace{
	0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
};

const std::array<float, 12> rightFace{
	1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
};

const std::array<float, 12> topFace{
	0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
};

const std::array<GLfloat, 12> bottomFace{ 
	0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 
};

ChunkMeshBuilder::ChunkMeshBuilder(Chunk* chunk)
	: chunk(chunk) {

}

void ChunkMeshBuilder::build() {
	curBlock = &chunk->firstBlock();

	for (int i = 0; i < CHUNK_VOL; ++i) {
		Block block = *(curBlock++);

		if (block.type->id == AIR)
			continue;

		setActiveMesh(block);

		glm::vec3 pos = Chunk::getLocalBlockPosition(i);

		BlockType blockType = *block.type;
		BlockFaces blockFaces(pos);
		
		if (pos.y >= 0)
			tryAddFace(bottomFace, blockType.texBottomCoords, pos, blockFaces.bottom, blockType);
		tryAddFace(topFace, blockType.texTopCoords, pos, blockFaces.top, blockType);

		tryAddFace(rightFace, blockType.texSideCoords, pos, blockFaces.right, blockType);
		tryAddFace(leftFace, blockType.texSideCoords, pos, blockFaces.left, blockType);

		tryAddFace(frontFace, blockType.texSideCoords, pos, blockFaces.front, blockType);
		tryAddFace(backFace, blockType.texSideCoords, pos, blockFaces.back, blockType);
	}
}

void ChunkMeshBuilder::setActiveMesh(Block& block) {
	if (block.type->shaderType == SOLID)
		activeMesh = chunk->getMeshes().solid;
	else if (block.type->shaderType == WATER)
		activeMesh = chunk->getMeshes().water;
}

void ChunkMeshBuilder::tryAddFace(const std::array<float, 12>& face,
		glm::vec2& texCoords,
		glm::vec3& localBlockPosition,
		glm::vec3& adjacentDir,
		BlockType blockType) {
	
	if (shouldAddFace(adjacentDir, blockType)) {
		std::array<float, 8> fTexCoords = BlocksDatabase::textureAtlas.getTexture(texCoords);

		activeMesh->addBlockFace(face, fTexCoords, chunk->getLocalPosition(), localBlockPosition);
	}
}

bool ChunkMeshBuilder::shouldAddFace(glm::vec3 adjacentDir, BlockType blockType) {
	BlockType adjBlockType = *chunk->getBlock(adjacentDir).type;
	
	if (adjBlockType.id == BlockID::AIR) {
		return true;
	}
	
	if (!adjBlockType.isOpaque && blockType.id != adjBlockType.id) {
		return true;
	}

	return false;
}