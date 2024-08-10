#include "ChunkMeshBuilder.h"

#include "../block/Block.h"
#include "../block/BlockFaces.h"

const std::array<float, 12> frontFace{ 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, };
const std::array<float, 12> backFace{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, };
const std::array<float, 12> leftFace{ 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, };
const std::array<float, 12> rightFace{ 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, };
const std::array<float, 12> topFace{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, };
const std::array<GLfloat, 12> bottomFace{ 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 };

const std::array<float, 12> xSide1{ 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, };
const std::array<float, 12> xSide2{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, };

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
	for (int i = 0; i < CHUNK_VOL; ++i) {
		Block* block = chunk->blocks[i];
		const BlockType* blockType = block->type;

		if (blockType->id == AIR)
			continue;

		setActiveMesh(blockType);

		glm::vec3 blockPos = Chunk::getLocalBlockPosition(i);

		if (blockType->meshType == MeshType::CUBE) {
			addCube(blockPos, blockType);
		} else if (blockType->meshType == MeshType::X) {
			addX(blockPos, blockType);
		}
	}
}

void ChunkMeshBuilder::setActiveMesh(const BlockType* blockType) {
	if (blockType->shaderType == BlockShaderType::SOLID)
		activeMesh = chunk->getMeshes().solid;
	else if (blockType->shaderType == BlockShaderType::WATER)
		activeMesh = chunk->getMeshes().water;
	else if (blockType->shaderType == BlockShaderType::FLORA)
		activeMesh = chunk->getMeshes().flora;
}

void ChunkMeshBuilder::addX(const glm::vec3& blockPos, const BlockType* blockType) {
	AtlasCoords atlasCoords = BlocksDatabase::getTextureAtlas().getTextureCoords(blockType->texSideCoords);

	activeMesh->addBlockFace(xSide1, atlasCoords, chunk->getLocalPosition(), blockPos);
	activeMesh->addBlockFace(xSide2, atlasCoords, chunk->getLocalPosition(), blockPos);
}

void ChunkMeshBuilder::addCube(const glm::vec3& blockPos, const BlockType* blockType) {
	BlockFaces blockFaces(blockPos);

	tryAddFace(bottomFace, blockType->texBottomCoords, bottomFaceNormal, blockPos, blockFaces.bottom, blockType);
	tryAddFace(topFace, blockType->texTopCoords, topFaceNormal, blockPos, blockFaces.top, blockType);

	tryAddFace(rightFace, blockType->texSideCoords, rightFaceNormal, blockPos, blockFaces.right, blockType);
	tryAddFace(leftFace, blockType->texSideCoords, leftFaceNormal, blockPos, blockFaces.left, blockType);

	tryAddFace(frontFace, blockType->texSideCoords, frontFaceNormal, blockPos, blockFaces.front, blockType);
	tryAddFace(backFace, blockType->texSideCoords, backFaceNormal, blockPos, blockFaces.back, blockType);
}

void ChunkMeshBuilder::tryAddFace(const std::array<float, 12>& vertices,
	const glm::vec2& texCoords,
	const glm::vec3& normal,
	const glm::vec3& localBlockPosition,
	const glm::vec3& adjacentDir,
	const BlockType* blockType) {
	
	if (localBlockPosition.y < 0)
		return;

	if (shouldAddFace(adjacentDir, blockType)) {
		AtlasCoords atlasCoords = BlocksDatabase::getTextureAtlas().getTextureCoords(texCoords);

		activeMesh->addBlockFace(vertices, atlasCoords, chunk->getLocalPosition(), localBlockPosition, normal);
	}
}

bool ChunkMeshBuilder::shouldAddFace(glm::vec3 adjacentDir, const BlockType* blockType) {
	Block* adjBlock = chunk->getBlock(adjacentDir);
	if (adjBlock == nullptr)
		return true;

	const BlockType* adjBlockType = adjBlock->type;

	if (adjBlockType->id == BlockID::AIR 
		|| (!adjBlockType->isOpaque && blockType->id != adjBlockType->id)) {
		return true;
	}

	return false;
}