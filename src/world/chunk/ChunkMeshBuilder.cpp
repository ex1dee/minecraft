#include "ChunkMeshBuilder.h"

#include "../block/BlockFaces.h"
#include "../block/BlockType.h"

const std::array<float, 12> frontFace{ 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, };
const std::array<float, 12> backFace{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, };
const std::array<float, 12> leftFace{ 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, };
const std::array<float, 12> rightFace{ 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, };
const std::array<float, 12> topFace{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, };
const std::array<GLfloat, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };

const glm::vec3 frontFaceNormal{ 0, 0, 1 };
const glm::vec3 backFaceNormal{ 0, 0, -1 };
const glm::vec3 leftFaceNormal{ -1, 0, 0 };
const glm::vec3 rightFaceNormal{ 1, 0, 0 };
const glm::vec3 topFaceNormal{ 0, 1, 0 };
const glm::vec3 bottomFaceNormal{ 0, -1, 0 };

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
			tryAddFace(bottomFace, blockType.texBottomCoords, bottomFaceNormal, pos, blockFaces.bottom, blockType);
		tryAddFace(topFace, blockType.texTopCoords, topFaceNormal, pos, blockFaces.top, blockType);

		tryAddFace(rightFace, blockType.texSideCoords, rightFaceNormal, pos, blockFaces.right, blockType);
		tryAddFace(leftFace, blockType.texSideCoords, leftFaceNormal, pos, blockFaces.left, blockType);

		tryAddFace(frontFace, blockType.texSideCoords, frontFaceNormal, pos, blockFaces.front, blockType);
		tryAddFace(backFace, blockType.texSideCoords, backFaceNormal, pos, blockFaces.back, blockType);
	}
}

void ChunkMeshBuilder::setActiveMesh(Block& block) {
	if (block.type->shaderType == SOLID)
		activeMesh = chunk->getMeshes().solid;
	else if (block.type->shaderType == WATER)
		activeMesh = chunk->getMeshes().water;
}

void ChunkMeshBuilder::tryAddFace(const std::array<float, 12>& vertices,
	const glm::vec2& texCoords,
	const glm::vec3& normal,
	const glm::vec3& localBlockPosition,
	const glm::vec3& adjacentDir,
	const BlockType& blockType) {
	
	if (shouldAddFace(adjacentDir, blockType)) {
		std::array<float, 8> fTexCoords = BlocksDatabase::textureAtlas.getTexture(texCoords);

		activeMesh->addBlockFace(vertices, fTexCoords, normal, chunk->getLocalPosition(), localBlockPosition);
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