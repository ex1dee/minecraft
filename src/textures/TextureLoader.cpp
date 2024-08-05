#include "TextureLoader.h"

#include <string>

#include "../utils/Files.h"

std::unordered_map<const char*, Texture*> TextureLoader::textures;

const TextureAtlas* const TextureLoader::loadAtlas(const char* path, const glm::vec2& imagesCount, bool flip, TextureType type) {
	TextureAtlas* texture = getTexture<TextureAtlas>(path);

	if (texture == nullptr)
		return new TextureAtlas(path, imagesCount, flip, type);

	return texture;
}

const BasicTexture* const TextureLoader::loadBasic(const char* path, bool flip, TextureType type) {
	BasicTexture* texture = getTexture<BasicTexture>(path);

	if (texture == nullptr)
		return new BasicTexture(path, flip, type);

	return texture;
}

const CubeTexture* const TextureLoader::loadCube(const char* directory, std::array<const char*, 6>& fileNames, bool flip) {
	CubeTexture* texture = getTexture<CubeTexture>(directory);

	if (texture == nullptr)
		return new CubeTexture(directory, fileNames, flip);
	
	return texture;
}

template<typename T> 
static T* const TextureLoader::getTexture(const char* key) {
	if (textures.find(key) != textures.end()) {
		return nullptr;
	} else {
		Texture* texture = textures[key];

		return (T*) texture;
	}
}