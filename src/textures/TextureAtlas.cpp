#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type, bool unloadImage)
	: BasicTexture(path, flip, type, unloadImage) {
	this->indvTextureSize = 1.0f / imagesCount;
}

AtlasCoords TextureAtlas::getTextureCoords(const glm::vec2& position) const {
	float dx = image.nchannels == 4 ? 0.001f : 0.0f;

	float xMin = position.x * indvTextureSize.x + dx;
	float xMax = xMin + indvTextureSize.x - dx;

	float yMin = position.y * indvTextureSize.y;
	float yMax = yMin + indvTextureSize.y;

	return AtlasCoords(false, xMin, xMax, yMin, yMax);
}

AtlasCoords TextureAtlas::getTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const {
	float dx = image.nchannels == 4 ? 0.001f : 0.0f;

	float xMin = bottomLeft.x * indvTextureSize.x + dx;
	float xMax = topRight.x * indvTextureSize.x - dx;

	float yMin = bottomLeft.y * indvTextureSize.y;
	float yMax = topRight.y * indvTextureSize.y;

	return AtlasCoords(false, xMin, xMax, yMin, yMax);
}

AtlasCoords TextureAtlas::getExactTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const {
	return AtlasCoords(true, bottomLeft / (float)getWidth(), topRight / (float)getHeight());
}