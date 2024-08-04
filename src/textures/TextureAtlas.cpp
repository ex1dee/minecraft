#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const char* path, const glm::vec2& imagesCount, bool flip, TextureType type)
	: BasicTexture(path, flip, type) {
	this->indvTextureSize = 1.0f / imagesCount;
}

std::array<float, 8> TextureAtlas::getTexture(const glm::vec2& coords) const {
	float xMin = coords.x * indvTextureSize.x;
	float xMax = xMin + indvTextureSize.x;
	
	float yMin = coords.y * indvTextureSize.y;
	float yMax = yMin + indvTextureSize.y;

	return {
		xMin, yMin,
		xMax, yMin,
		xMax, yMax,
		xMin, yMax
	};
}