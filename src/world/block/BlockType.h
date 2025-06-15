#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

#include <glm/glm.hpp>
#include <string>

#include "../../sounds/SoundSource.h"
#include "../../render/model/Mesh.h"
#include "../../items/Material.h"
#include "meta/BlockMetaLoader.h"
#include "BlockColliders.h"
#include "BlockShaderType.h"

class BlockType : public SoundSource {
public:
	Material material;
	std::unique_ptr<BlockMeta> meta;
	std::vector<std::unique_ptr<BoxCollider>> colliders;
	BlockShaderType shaderType;
	glm::vec2 texTopCoords;
	glm::vec2 texBottomCoords;
	glm::vec2 texSideCoords;
	MeshType meshType;
	bool isOpaque;
	bool isSolid;
};

#endif