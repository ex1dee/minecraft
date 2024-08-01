#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <glm/glm.hpp>

#include "../../render/Mesh.h"
#include "BlockColliders.h"
#include "BlockShaderType.h"
#include "BlockID.h"

struct BlockType {
	BlockID id;
	bool isOpaque;
	bool isSolid;
	MeshType meshType;
	BlockShaderType shaderType;
	glm::vec2 texTopCoords;
	glm::vec2 texBottomCoords;
	glm::vec2 texSideCoords;
	std::vector<BoxCollider*> colliders;
};

#endif