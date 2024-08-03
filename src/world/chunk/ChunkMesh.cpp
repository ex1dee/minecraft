#include "ChunkMesh.h"

ChunkMesh::~ChunkMesh() {
	model.reset();
}

void ChunkMesh::addBlockFace(const std::array<float, 12>& vertices,
	const std::array<float, 8>& texCoords,
	const glm::vec3& normal,
	const glm::vec2& localChunkPosition,
	const glm::vec3& localBlockPosition) {

	int index = 0;

	for (int i = 0; i < 4; ++i) {
		mesh.vertexPositions.push_back(vertices[index++] + localChunkPosition.x * CHUNK_W + localBlockPosition.x);
		mesh.vertexPositions.push_back(vertices[index++] + localBlockPosition.y);
		mesh.vertexPositions.push_back(vertices[index++] + localChunkPosition.y * CHUNK_D + localBlockPosition.z);

		mesh.normals.push_back(normal.x);
		mesh.normals.push_back(normal.y);
		mesh.normals.push_back(normal.z);
	}

	mesh.textureCoords.insert(mesh.textureCoords.end(), texCoords.begin(), texCoords.end());

	mesh.indices.push_back(vertIndex);
	mesh.indices.push_back(vertIndex + 1);
	mesh.indices.push_back(vertIndex + 2);

	mesh.indices.push_back(vertIndex);
	mesh.indices.push_back(vertIndex + 2);
	mesh.indices.push_back(vertIndex + 3);

	vertIndex += 4;
	faces++;
}

void ChunkMesh::createBuffers() {
	model.addMesh(mesh, 3);

	mesh.reset();
	vertIndex = 0;
	faces = 0;
}