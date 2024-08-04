#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <unordered_map>

#include "BasicTexture.h"
#include "CubeTexture.h"
#include "TextureAtlas.h"

class TextureLoader {
	static std::unordered_map<const char*, Texture*> textures;

	template<typename T> static T* getTexture(const char* key);
public:
	static TextureAtlas* loadAtlas(const char* path, const glm::vec2& imagesCount, bool flip, TextureType type);
	static BasicTexture* loadBasic(const char* path, bool flip, TextureType type);
	static CubeTexture* loadCube(const char* directory, std::array<const char*, 6>& fileNames, bool flip);
};

#endif