#include "BlocksDatabase.h"

#include "../../utils/Json.h"

std::unordered_map<int, BlockType*> BlocksDatabase::blocks;
TextureAtlas BlocksDatabase::textureAtlas;

void BlocksDatabase::initialize() {
	textureAtlas = TextureAtlas("resources/textures/blocks_atlas.png", glm::vec2(16, 16), true, DIFFUSE);

	for (std::string path : Files::getFolderFiles(BLOCKS_DIR)) {
		nlohmann::json json = Json::parse(path.c_str());
		
		BlockType* type = new BlockType();
		type->texBottomCoords = glm::vec2(json["texCoords"]["bottom"]["x"], json["texCoords"]["bottom"]["y"]);
		type->texSideCoords = glm::vec2(json["texCoords"]["side"]["x"], json["texCoords"]["side"]["y"]);
		type->texTopCoords = glm::vec2(json["texCoords"]["top"]["x"], json["texCoords"]["top"]["y"]);
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
	for (int i = 0; i < blocks.size(); ++i) {
		delete blocks[i];
	}
}