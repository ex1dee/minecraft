#ifndef ITEMTYPE_H
#define ITEMTYPE_H

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
};

#endif