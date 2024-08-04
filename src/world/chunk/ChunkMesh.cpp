#include "ChunkMesh.h"

void ChunkMesh::addBlockFace(const std::array<float, 12>& vertices,
	const std::array<float, 8>& texCoords,
	const glm::vec2& localChunkPosition,
	const glm::vec3& localBlockPosition,
	const glm::vec3& normal) {

	int index = 0;

	for (int i = 0; i < 4; ++i) {
		meshData.vertexPositions.push_back(vertices[index++] + localChunkPosition.x * CHUNK_W + localBlockPosition.x);
		meshData.vertexPositions.push_back(vertices[index++] + localBlockPosition.y);
		meshData.vertexPositions.push_back(vertices[index++] + localChunkPosition.y * CHUNK_D + localBlockPosition.z);

		if (glm::length(normal) != 0) {
			meshData.normals.push_back(normal.x);
			meshData.normals.push_back(normal.y);
			meshData.normals.push_back(normal.z);
		}
	}

	meshData.textureCoords.insert(meshData.textureCoords.end(), texCoords.begin(), texCoords.end());

	meshData.indices.push_back(vertIndex);
	meshData.indices.push_back(vertIndex + 1);
	meshData.indices.push_back(vertIndex + 2);

	meshData.indices.push_back(vertIndex);
	meshData.indices.push_back(vertIndex + 2);
	meshData.indices.push_back(vertIndex + 3);

	vertIndex += 4;
	faces++;
}

void ChunkMesh::createBuffers() {
	model.reset();
	model.addMesh(meshData);

	vertIndex = 0;
	faces = 0;
}