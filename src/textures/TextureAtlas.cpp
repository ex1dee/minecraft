#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const char* path, glm::vec2 imagesCount, bool flip)
	: BasicTexture(path, flip) {
	this->indvTextureSize = 1.0f / imagesCount;
}

std::array<float, 8> TextureAtlas::getTexture(glm::vec2 coords) {
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