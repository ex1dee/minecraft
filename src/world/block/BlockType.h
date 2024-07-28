#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <glm/glm.hpp>

#include "../../render/mesh/MeshType.h"
#include "ShaderType.h"
#include "BlockID.h"

class BlockType {
public:
	BlockID id;
	bool isOpaque;
	MeshType meshType;
	ShaderType shaderType;
	glm::vec2 texTopCoords;
	glm::vec2 texBottomCoords;
	glm::vec2 texSideCoords;
};

#endif