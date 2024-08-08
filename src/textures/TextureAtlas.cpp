#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const char* path, const glm::vec2& imagesCount, bool flip, TextureType type)
	: BasicTexture(path, flip, type) {
	this->indvTextureSize = 1.0f / imagesCount;
}

AtlasCoords TextureAtlas::getTextureCoords(const glm::vec2& position) const {
	float xMin = position.x * indvTextureSize.x;
	float xMax = xMin + indvTextureSize.x;

	float yMin = position.y * indvTextureSize.y;
	float yMax = yMin + indvTextureSize.y;

	return AtlasCoords(false, xMin, xMax, yMin, yMax);
}

AtlasCoords TextureAtlas::getTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const {
	float xMin = bottomLeft.x * indvTextureSize.x;
	float xMax = topRight.x * indvTextureSize.x;

	float yMin = bottomLeft.y * indvTextureSize.y;
	float yMax = topRight.y * indvTextureSize.y;

	return AtlasCoords(false, xMin, xMax, yMin, yMax);
}

AtlasCoords TextureAtlas::getExactTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const {
	return AtlasCoords(true, bottomLeft / (float)getWidth(), topRight / (float)getHeight());
}