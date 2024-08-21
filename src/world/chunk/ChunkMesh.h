#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <glm/glm.hpp>
#include <array>

#include "../../textures/AtlasCoords.h"
#include "../../render/model/Model.h"
#include "../WorldConstants.h"

class ChunkMesh {
	MeshData meshData = MeshData(MeshType::CUBE, 3);
	Model model;
	int vertIndex;
	int faces;
public:
	void addBlockFace(const std::array<float, 12>& vertices, 
		const AtlasCoords& texCoords, 
		const glm::vec2& localChunkPosition,
		const glm::vec3& localBlockPosition,
		const glm::vec3& normal = glm::vec3(0));
	void createBuffers();

	Model& getModel() { return model; }
	int getFaces() { return faces; }
};

struct ChunkMeshCollection {
	std::shared_ptr<ChunkMesh> solid;
	std::shared_ptr<ChunkMesh> liquid;
	std::shared_ptr<ChunkMesh> flora;

	ChunkMeshCollection() {
		solid = std::make_shared<ChunkMesh>();
		liquid = std::make_shared<ChunkMesh>();
		flora = std::make_shared<ChunkMesh>();
	}

	void createBuffers() {
		solid->createBuffers();
		liquid->createBuffers();
		flora->createBuffers();
	}

	void setAABB(const AABB& aabb) {
		solid->getModel().aabb = aabb;
		liquid->getModel().aabb = aabb;
		flora->getModel().aabb = aabb;
	}
};

#endif