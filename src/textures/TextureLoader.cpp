#include "TextureLoader.h"

#include <string>

#include "../utils/Files.h"

std::unordered_map<std::string, Texture*> TextureLoader::textures;

void TextureLoader::loadSprite(const nlohmann::basic_json<>& json, SpriteTexture& texture) {
	nlohmann::basic_json<> atlasJson = json["atlas"];
	std::string path = json["path"];

	texture.useAtlas = atlasJson["use"];

	if (texture.useAtlas) {
		glm::vec2 imagesCount = atlasJson.contains("imagesCount") ? Json::toVec2(atlasJson["imagesCount"]) : glm::vec2(0);

		const TextureAtlas* atlas = loadAtlas(path, imagesCount, true, TextureType::SPRITE);
		texture.data = (const Texture*)atlas;

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

const TextureAtlas* const TextureLoader::loadAtlas(const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type) {
	TextureAtlas* texture = getTexture<TextureAtlas>(path);

	if (texture == nullptr)
		return new TextureAtlas(path, imagesCount, flip, type);

	return texture;
}

const BasicTexture* const TextureLoader::loadBasic(const std::string& path, bool flip, TextureType type) {
	BasicTexture* texture = getTexture<BasicTexture>(path);

	if (texture == nullptr)
		return new BasicTexture(path, flip, type);

	return texture;
}

const CubeTexture* const TextureLoader::loadCube(const std::string& directory, std::array<std::string, 6>& fileNames, bool flip) {
	CubeTexture* texture = getTexture<CubeTexture>(directory);

	if (texture == nullptr)
		return new CubeTexture(directory, fileNames, flip);
	
	return texture;
}

template<typename T> 
static T* const TextureLoader::getTexture(const std::string& key) {
	if (textures.find(key) != textures.end()) {
		return nullptr;
	} else {
		Texture* texture = textures[key];

		return (T*) texture;
	}
}