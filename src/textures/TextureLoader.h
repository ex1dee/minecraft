#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <unordered_map>

#include "BasicTexture.h"
#include "CubeTexture.h"
#include "TextureAtlas.h"

class TextureLoader {
	static std::unordered_map<const char*, Texture*> textures;

	template<typename T> static T* const getTexture(const char* key);
public:
	static const TextureAtlas* const loadAtlas(const char* path, const glm::vec2& imagesCount, bool flip, TextureType type);
	static const BasicTexture* const loadBasic(const char* path, bool flip, TextureType type);
	static const CubeTexture* const loadCube(const char* directory, std::array<const char*, 6>& fileNames, bool flip);
};

#endif