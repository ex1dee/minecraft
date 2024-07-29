#include "ChunkMesh.h"

ChunkMesh::~ChunkMesh() {
	model.reset();
}

void ChunkMesh::addBlockFace(const std::array<float, 12>& face,
			std::array<float, 8>& texCoords,
			glm::vec2 localChunkPosition,
			glm::vec3 localBlockPosition) {
	int index = 0;

	for (int i = 0; i < 4; ++i) {
		mesh.vertexPositions.push_back(face[index++] + localChunkPosition.x * CHUNK_W + localBlockPosition.x);
		mesh.vertexPositions.push_back(face[index++] + localBlockPosition.y);
		mesh.vertexPositions.push_back(face[index++] + localChunkPosition.y * CHUNK_D + localBlockPosition.z);
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