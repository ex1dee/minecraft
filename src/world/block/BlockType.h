#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <glm/glm.hpp>

#include "../../render/model/Mesh.h"
#include "meta/BlockMetaLoader.h"
#include "BlockColliders.h"
#include "BlockShaderType.h"
#include "BlockType.h"
#include "BlockID.h"

class BlockType {
public:
	BlockID id;
	BlockMeta* meta;
	bool isOpaque;
	bool isSolid;
	MeshType meshType;
	BlockShaderType shaderType;
	glm::vec2 texTopCoords;
	glm::vec2 texBottomCoords;
	glm::vec2 texSideCoords;
	std::vector<BoxCollider*> colliders;

	~BlockType() {
		delete meta;
	}
};

#endif