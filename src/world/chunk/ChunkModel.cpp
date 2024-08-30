#include "ChunkModel.h"

ChunkModel::ChunkModel() {
	meshData = std::make_unique<MeshData>(MeshType::CUBE, 3);
	vertIndex = 0;
}

void ChunkModel::addBlockFace(const std::array<float, 12>& vertices,
	const AtlasCoords& texCoords,
	const glm::vec2& localChunkPosition,
	const glm::vec3& localBlockPosition,
	const glm::vec3& normal) {

	if (meshData == nullptr)
		meshData = std::make_unique<MeshData>(MeshType::CUBE, 3);

	for (int i = 0; i < 4; ++i) {
		meshData->vertexPositions.push_back(vertices[i * 3] + localChunkPosition.x * CHUNK_W + localBlockPosition.x);
		meshData->vertexPositions.push_back(vertices[i * 3 + 1] + localBlockPosition.y);
		meshData->vertexPositions.push_back(vertices[i * 3 + 2] + localChunkPosition.y * CHUNK_D + localBlockPosition.z);

		if (glm::length(normal) != 0) {
			meshData->normals.push_back(normal.x);
			meshData->normals.push_back(normal.y);
			meshData->normals.push_back(normal.z);
		}
	}
	
	texCoords.addToTexCoords(meshData->textureCoords);

	meshData->indices.push_back(vertIndex);
	meshData->indices.push_back(vertIndex + 1);
	meshData->indices.push_back(vertIndex + 2);

	meshData->indices.push_back(vertIndex);
	meshData->indices.push_back(vertIndex + 2);
	meshData->indices.push_back(vertIndex + 3);

	vertIndex += 4;
}

void ChunkModel::createBuffers() {
	reset();

	model.addMesh(meshData);
	meshData = std::make_unique<MeshData>(MeshType::CUBE, 3);
}

void ChunkModel::reset() {
	model.reset();

	vertIndex = 0;
}