#include "ItemMetaLoader.h"

#include "../../utils/StringConverter.h"

std::unique_ptr<ItemMeta> ItemMetaLoader::load(const nlohmann::basic_json<>& json) {
	std::unique_ptr<ItemMeta> meta = load((ItemMetaID) json["id"]);
	meta->setName(StringConverter::toWString(json["name"]));

	std::vector<std::wstring> lore;
	for (const std::string& line : json["lore"]) {
		lore.push_back(StringConverter::toWString(line));
	}

	meta->setLore(lore);

	return std::move(meta);
}

std::unique_ptr<ItemMeta> ItemMetaLoader::load(ItemMetaID id) {
	switch (id) {
	default:
		return std::move(std::make_unique<ItemMeta>());
	}
}