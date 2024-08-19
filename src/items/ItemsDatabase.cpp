#include "ItemsDatabase.h"

#include "../textures/TextureLoader.h"
#include "../utils/PointerUtils.h"
#include "meta/ItemMetaLoader.h"

std::unordered_map<Material, ItemType*> ItemsDatabase::items;

constexpr const char* ITEMS_DIR = "resources/items";

void ItemsDatabase::initialize() {
	for (const std::string& path : Files::getFolderFiles(ITEMS_DIR)) {
		nlohmann::json json = Json::parse(path);

		ItemType* type = new ItemType;

		type->material = json["material"];
		type->hasMeta = json["hasMeta"];

		nlohmann::basic_json id = json["meta"];

		if (type->hasMeta)
			type->meta = ItemMetaLoader::load(json["meta"]);

		TextureLoader::loadSprite(json["texture"], type->texture);

		items.emplace(type->material, type);
	}
}

void ItemsDatabase::finalize() {
	freeMapValues(items);
}