#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <glm/glm.hpp>
#include <array>

#include "../../render/model/Model.h"
#include "../WorldConstants.h"

class ChunkMesh {
	MeshData meshData = MeshData(CUBE, 3);
	Model model;
	int vertIndex;
	int faces;
public:
	void addBlockFace(const std::array<float, 12>& vertices, 
		const std::array<float, 8>& texCoords, 
		const glm::vec2& localChunkPosition,
		const glm::vec3& localBlockPosition,
		const glm::vec3& normal = glm::vec3(0));
	void createBuffers();

	Model& getModel() { return model; }
	int getFaces() { return faces; }
};

struct ChunkMeshCollection {
	ChunkMesh* solid;
	ChunkMesh* water;
	ChunkMesh* flora;

	ChunkMeshCollection() {
		solid = new ChunkMesh();
		water = new ChunkMesh();
		flora = new ChunkMesh();
	}

	~ChunkMeshCollection() {
		delete solid, water, flora;
	}

	void createBuffers() {
		solid->createBuffers();
		water->createBuffers();
		flora->createBuffers();
	}

	void setAABB(const AABB& aabb) {
		solid->getModel().aabb = aabb;
		water->getModel().aabb = aabb;
		flora->getModel().aabb = aabb;
	}
};

#endif