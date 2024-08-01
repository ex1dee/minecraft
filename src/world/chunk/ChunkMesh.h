#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <glm/glm.hpp>
#include <array>

#include "../../render/Model.h"
#include "../WorldConstants.h"

class ChunkMesh {
	Model model;
	Mesh mesh;
	int vertIndex;
	int faces;
public:
	ChunkMesh() {}
	~ChunkMesh();

	void addBlockFace(const std::array<float, 12>& vertices, 
		const std::array<float, 8>& texCoords, 
		const glm::vec3& normal,
		const glm::vec2& localChunkPosition,
		const glm::vec3& localBlockPosition);
	void createBuffers();

	Model& getModel() { return model; }
	int getFaces() { return faces; }
};

struct ChunkMeshCollection {
	ChunkMesh* solid;
	ChunkMesh* water;

	ChunkMeshCollection() {
		solid = new ChunkMesh();
		water = new ChunkMesh();
	}

	~ChunkMeshCollection() {
		delete solid, water;
	}

	void createBuffers() {
		solid->createBuffers();
		water->createBuffers();
	}

	void setAABB(const AABB& aabb) {
		solid->getModel().aabb = aabb;
		water->getModel().aabb = aabb;
	}
};

#endif