#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include "../world/block/BlocksDatabase.h"
#include "../textures/SpriteTexture.h"
#include "meta/ItemMeta.h"
#include "Material.h"

class ItemType {
public:
	std::unique_ptr<ItemMeta> meta;
	SpriteTexture texture;
	Material material;
	int maxAmount;
	bool hasMeta;

	bool hasCubeMesh() const { return BlocksDatabase::contains(material) && BlocksDatabase::get(material).meshType == MeshType::CUBE; }
};

#endif