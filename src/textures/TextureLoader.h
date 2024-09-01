#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <unordered_map>

#include "../utils/Json.h"
#include "SpriteTexture.h"
#include "TextureAtlas.h"
#include "BasicTexture.h"
#include "CubeTexture.h"

class TextureLoader {
	static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

	template<typename T> static std::shared_ptr<T> getTexture(const std::string& key);
public:
	static void loadSprite(
		const nlohmann::basic_json<>& json, SpriteTexture& texture, bool unloadImage = true
	);

	static std::shared_ptr<TextureAtlas> loadAtlas(
		const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type, bool unloadImage = true
	);

	static std::shared_ptr<BasicTexture> loadBasic(
		const std::string& path, bool flip, TextureType type, bool unloadImage = true
	);

	static std::shared_ptr<CubeTexture> loadCube(
		const std::string& directory, std::array<std::string, 6>& fileNames, bool flip, bool unloadImage = true
	);
};

#endif