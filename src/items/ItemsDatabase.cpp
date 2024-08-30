#include "ItemsDatabase.h"

#include "../textures/TextureLoader.h"
#include "meta/ItemMetaLoader.h"

std::unordered_map<Material, std::unique_ptr<ItemType>> ItemsDatabase::items;

constexpr const char* ITEMS_DIR = "resources/items";

void ItemsDatabase::initialize() {
	for (const std::string& path : Files::getFolderFiles(ITEMS_DIR)) {
		std::unique_ptr<ItemType> type = std::make_unique<ItemType>();
		nlohmann::json json = Json::parse(path);

		type->material = json["material"];
		type->hasMeta = json["hasMeta"];
		type->maxAmount = json["maxAmount"];

		nlohmann::basic_json id = json["meta"];

		if (type->hasMeta)
			type->meta = ItemMetaLoader::load(json["meta"]);

		TextureLoader::loadSprite(json["texture"], type->texture);

		items.emplace(type->material, std::move(type));
	}
}