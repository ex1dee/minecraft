#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <glm/glm.hpp>
#include <array>

#include "BasicTexture.h"
#include "AtlasCoords.h"

class TextureAtlas : public BasicTexture {
	glm::vec2 indvTextureSize;
public:
	TextureAtlas() = default;
	TextureAtlas(const std::string& path, const glm::vec2& imagesCount, bool flip, TextureType type, bool unloadImage = true);

	AtlasCoords getTextureCoords(const glm::vec2& position) const;
	AtlasCoords getTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;
	AtlasCoords getExactTextureCoords(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;
};

#endif