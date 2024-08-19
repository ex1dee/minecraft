#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <glm/glm.hpp>

#include "../../utils/PointerUtils.h"
#include "../../render/model/Mesh.h"
#include "../../items/Material.h"
#include "meta/BlockMetaLoader.h"
#include "BlockColliders.h"
#include "BlockShaderType.h"

class BlockType {
public:
	Material material;
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
		freePointer(&meta);
	}
};

#endif