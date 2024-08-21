#include "BlocksDatabase.h"

#include "meta/BlockMetaLoader.h"
#include "../../utils/Json.h"

constexpr const char* BLOCKS_DIR = "resources/blocks";

std::unordered_map<Material, std::unique_ptr<BlockType>> BlocksDatabase::blocks;
std::shared_ptr<TextureAtlas> BlocksDatabase::textureAtlas;

void BlocksDatabase::initialize() {
	textureAtlas = TextureLoader::loadAtlas("resources/textures/blocks_atlas.png", glm::vec2(16, 16), true, TextureType::DIFFUSE);

	for (const std::string& path : Files::getFolderFiles(BLOCKS_DIR)) {
		nlohmann::json json = Json::parse(path);

		std::unique_ptr<BlockType> type = std::make_unique<BlockType>();
		type->texBottomCoords = Json::toVec2(json["texCoords"]["bottom"]);
		type->texSideCoords = Json::toVec2(json["texCoords"]["side"]);
		type->texTopCoords = Json::toVec2(json["texCoords"]["top"]);
		type->colliders = BlockColliders::get(json["colliderType"]);
		type->shaderType = json["shaderType"];
		type->meshType = json["meshType"];
		type->isOpaque = json["opaque"];
		type->isSolid = json["solid"];
		type->material = json["material"];

		if (json.find("meta") != json.end()) {
			type->meta = BlockMetaLoader::load(json["meta"]["id"], json);
		}

		blocks.emplace(type->material, std::move(type));
	}
}