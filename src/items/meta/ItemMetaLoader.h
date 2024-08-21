#ifndef ITEMMETALOADER_H
#define ITEMMETALOADER_H

#include "../../utils/Json.h"
#include "ItemMeta.h"

class ItemMetaLoader {
	static std::unique_ptr<ItemMeta> load(ItemMetaID id);
public:
	static std::unique_ptr<ItemMeta> load(const nlohmann::basic_json<>& json);
};

#endif