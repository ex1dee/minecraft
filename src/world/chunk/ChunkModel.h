#ifndef CHUNKMODEL_H
#define CHUNKMODEL_H

#include <glm/glm.hpp>
#include <array>

#include "../../textures/AtlasCoords.h"
#include "../../render/model/Model.h"
#include "../WorldConstants.h"

class ChunkModel {
	std::unique_ptr<MeshData> meshData;
	Model model;
	int vertIndex;
public:
	ChunkModel();

	Model& getModel() { return model; }

	void addBlockFace(const std::array<float, 12>& vertices, 
		const AtlasCoords& texCoords, 
		const glm::vec2& localChunkPosition,
		const glm::vec3& localBlockPosition,
		const glm::vec3& normal = glm::vec3(0));
	void createBuffers();
	void reset();
};

struct ChunkModelCollection {
	std::shared_ptr<ChunkModel> solid;
	std::shared_ptr<ChunkModel> liquid;
	std::shared_ptr<ChunkModel> flora;

	ChunkModelCollection() {
		solid = std::make_shared<ChunkModel>();
		liquid = std::make_shared<ChunkModel>();
		flora = std::make_shared<ChunkModel>();
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

	void reset() {
		solid->reset();
		liquid->reset();
		flora->reset();
	}
};

#endif