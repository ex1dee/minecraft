#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include "../textures/SpriteTexture.h"
#include "../utils/PointerUtils.h"
#include "meta/ItemMeta.h"
#include "Material.h"

class ItemType {
public:
	SpriteTexture texture;
	Material material;
	ItemMeta* meta;
	bool hasMeta;

	~ItemType() {
		freePointer(&meta);
	}
};

#endif