#include "BlocksDatabase.h"

#include "../../utils/Json.h"

std::unordered_map<BlockID, BlockType*> BlocksDatabase::blocks;
const TextureAtlas* BlocksDatabase::textureAtlas;

void BlocksDatabase::initialize() {
	textureAtlas = TextureLoader::loadAtlas("resources/textures/blocks_atlas.png", glm::vec2(16, 16), true, TextureType::DIFFUSE);

	for (std::string path : Files::getFolderFiles(BLOCKS_DIR)) {
		nlohmann::json json = Json::parse(path.c_str());

		BlockType* type = new BlockType;
		type->texBottomCoords = Json::toVec2(json["texCoords"]["bottom"]);
		type->texSideCoords = Json::toVec2(json["texCoords"]["side"]);
		type->texTopCoords = Json::toVec2(json["texCoords"]["top"]);
		type->colliders = BlockColliders::get(json["colliderType"]);
		type->shaderType = json["shaderType"];
		type->meshType = json["meshType"];
		type->isOpaque = json["opaque"];
		type->isSolid = json["solid"];
		type->id = json["id"];

		blocks.emplace(type->id, type);
	}
}

void BlocksDatabase::finalize() {
	for (std::pair<int, BlockType*> pair : blocks) {
		delete pair.second;
	}
}