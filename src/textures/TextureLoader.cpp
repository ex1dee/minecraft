#include "TextureLoader.h"

#include <string>

#include "../utils/Files.h"

std::unordered_map<std::string, std::shared_ptr<Texture>> TextureLoader::textures;

void TextureLoader::loadSprite(const nlohmann::basic_json<>& json, SpriteTexture& texture) {
	nlohmann::basic_json<> atlasJson = json["atlas"];
	std::string path = json["path"];

	texture.useAtlas = atlasJson["use"];

	if (texture.useAtlas) {
		glm::vec2 imagesCount = atlasJson.contains("imagesCount") ? Json::toVec2(atlasJson["imagesCount"]) : glm::vec2(0);

		std::shared_ptr<TextureAtlas> atlas = loadAtlas(path, imagesCount, true, TextureType::SPRITE);
		texture.data = std::static_pointer_cast<Texture>(atlas);

		glm::vec2 bottomLeft = Json::toVec2(atlasJson["bottomLeft"]);
		glm::vec2 topRight = Json::toVec2(atlasJson["topRight"]);
		texture.atlas.exactly = atlasJson["exactCoords"];

		if (texture.atlas.exactly) {
			texture.atlas = atlas->getExactTextureCoords(bottomLeft, topRight);
		} else {
			texture.atlas = atlas->getTextureCoords(bottomLeft, topRight);
		}
	} else {
		texture.data = loadBasic(path, true, TextureType::SPRITE);
	}
}

std::shared_ptr<TextureAtlas> TextureLoader::loadAtlas(const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type) {
	std::shared_ptr<TextureAtlas> texture = getTexture<TextureAtlas>(path);

	if (texture == nullptr) {
		textures.emplace(path, std::make_shared<TextureAtlas>(path, imagesCount, flip, type));
		texture = getTexture<TextureAtlas>(path);
	}

	return texture;
}

std::shared_ptr<BasicTexture> TextureLoader::loadBasic(const std::string& path, bool flip, TextureType type) {
	std::shared_ptr<BasicTexture> texture = getTexture<BasicTexture>(path);

	if (texture == nullptr) {
		textures.emplace(path, std::make_shared<BasicTexture>(path, flip, type));
		texture = getTexture<BasicTexture>(path);
	}

	return texture;
}

std::shared_ptr<CubeTexture> TextureLoader::loadCube(const std::string& directory, std::array<std::string, 6>& fileNames, bool flip) {
	std::shared_ptr<CubeTexture> texture = getTexture<CubeTexture>(directory);

	if (texture == nullptr) {
		textures.emplace(directory, std::make_shared<CubeTexture>(directory, fileNames, flip));
		texture = getTexture<CubeTexture>(directory);
	}
	
	return texture;
}

template<typename T> 
static std::shared_ptr<T> TextureLoader::getTexture(const std::string& key) {
	if (textures.find(key) != textures.end()) {
		return std::dynamic_pointer_cast<T>(textures[key]);
	} else {
		return nullptr;
	}
}