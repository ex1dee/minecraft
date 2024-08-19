#include "ItemMetaLoader.h"

#include "../../utils/StringConverter.h"

ItemMeta* ItemMetaLoader::load(const nlohmann::basic_json<>& json) {
	ItemMeta* meta = load((ItemMetaID) json["id"]);
	meta->setName(StringConverter::toWString(json["name"]));

	std::vector<std::wstring> lore;
	for (const std::string& line : json["lore"]) {
		lore.push_back(StringConverter::toWString(line));
	}

	meta->setLore(lore);

	return meta;
}

ItemMeta* ItemMetaLoader::load(ItemMetaID id) {
	switch (id) {
	default:
		return new ItemMeta;
	}
}