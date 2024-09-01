#include "ChunkModelBuilder.h"

#include "../block/BlockMeshConstants.h"
#include "../block/BlockFaces.h"
#include "../block/Block.h"

ChunkModelBuilder::ChunkModelBuilder(Chunk& chunk, ChunkModelCollection& model)
	: chunk(&chunk), model(&model) {

}

void ChunkModelBuilder::build() {
	for (int i = 0; i < CHUNK_VOL; ++i) {
		std::shared_ptr<Block> block = chunk->blocks[i];
		const BlockType& blockType = block->getType();

		if (blockType.material == AIR)
			continue;

		setActiveMesh(blockType);

		glm::vec3 blockPos = Chunk::getLocalBlockPosition(i);

		if (blockType.meshType == MeshType::CUBE) {
			addCube(blockPos, blockType);
		} else if (blockType.meshType == MeshType::X) {
			addX(blockPos, blockType);
		}
	}
}

void ChunkModelBuilder::setActiveMesh(const BlockType& blockType) {
	if (blockType.shaderType == BlockShaderType::SOLID)
		activeMesh = model->solid;
	else if (blockType.shaderType == BlockShaderType::LIQUID)
		activeMesh = model->liquid;
	else if (blockType.shaderType == BlockShaderType::FLORA)
		activeMesh = model->flora;
}

void ChunkModelBuilder::addX(const glm::vec3& blockPos, const BlockType& blockType) {
	AtlasCoords atlasCoords = BlocksDatabase::getTextureAtlas()->getTextureCoords(blockType.texSideCoords);

	activeMesh->addBlockFace(xSide1, atlasCoords, chunk->getLocalPosition(), blockPos);
	activeMesh->addBlockFace(xSide2, atlasCoords, chunk->getLocalPosition(), blockPos);
}

void ChunkModelBuilder::addCube(const glm::vec3& blockPos, const BlockType& blockType) {
	BlockFaces blockFaces(blockPos);

	tryAddFace(bottomFace, blockType.texBottomCoords, bottomFaceNormal, blockPos, blockFaces.bottom, blockType);
	tryAddFace(topFace, blockType.texTopCoords, topFaceNormal, blockPos, blockFaces.top, blockType);

	tryAddFace(rightFace, blockType.texSideCoords, rightFaceNormal, blockPos, blockFaces.right, blockType);
	tryAddFace(leftFace, blockType.texSideCoords, leftFaceNormal, blockPos, blockFaces.left, blockType);

	tryAddFace(frontFace, blockType.texSideCoords, frontFaceNormal, blockPos, blockFaces.front, blockType);
	tryAddFace(backFace, blockType.texSideCoords, backFaceNormal, blockPos, blockFaces.back, blockType);
}

void ChunkModelBuilder::tryAddFace(const std::array<float, 12>& vertices,
	const glm::vec2& texCoords,
	const glm::vec3& normal,
	const glm::vec3& localBlockPosition,
	const glm::vec3& adjacentDir,
	const BlockType& blockType) {
	
	if (localBlockPosition.y < 0)
		return;

	if (shouldAddFace(adjacentDir, blockType)) {
		AtlasCoords atlasCoords = BlocksDatabase::getTextureAtlas()->getTextureCoords(texCoords);

		activeMesh->addBlockFace(vertices, atlasCoords, chunk->getLocalPosition(), localBlockPosition, normal);
	}
}

bool ChunkModelBuilder::shouldAddFace(glm::vec3 adjacentDir, const BlockType& blockType) {
	std::shared_ptr<Block> adjBlock = chunk->getBlock(adjacentDir);
	if (adjBlock == nullptr)
		return true;

	const BlockType& adjBlockType = adjBlock->getType();

	if (adjBlockType.material == Material::AIR 
		|| (!adjBlockType.isOpaque && blockType.material != adjBlockType.material)) {
		return true;
	}

	return false;
}