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

	void addBlockFace(const std::array<float, 12>& face, 
					  std::array<float, 8>& texCoords, 
					  glm::vec2 localChunkPosition,
					  glm::vec3 localBlockPosition);
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
};

#endif