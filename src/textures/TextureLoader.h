#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <unordered_map>

#include "../utils/Json.h"
#include "SpriteTexture.h"
#include "TextureAtlas.h"
#include "BasicTexture.h"
#include "CubeTexture.h"

class TextureLoader {
	static std::unordered_map<std::string, Texture*> textures;

	template<typename T> static T* const getTexture(const std::string& key);
public:
	static void loadSprite(const nlohmann::basic_json<>& json, SpriteTexture& texture);

	static const TextureAtlas* const loadAtlas(const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type);
	static const BasicTexture* const loadBasic(const std::string& path, bool flip, TextureType type);
	static const CubeTexture* const loadCube(const std::string& directory, std::array<std::string, 6>& fileNames, bool flip);
};

#endif