#ifndef ITEMMETALOADER_H
#define ITEMMETALOADER_H

#include "../../utils/Json.h"
#include "ItemMeta.h"

class ItemMetaLoader {
	static ItemMeta* load(ItemMetaID id);
public:
	static ItemMeta* load(const nlohmann::basic_json<>& json);
};

#endif