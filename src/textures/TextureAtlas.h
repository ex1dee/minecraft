#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "BasicTexture.h"

#include <glm/glm.hpp>
#include <array>

class TextureAtlas : public BasicTexture {
	glm::vec2 indvTextureSize;
public:
	TextureAtlas() {}
	TextureAtlas(const char* path, glm::vec2 imagesCount, bool flip, TextureType type);

	std::array<float, 8> getTexture(glm::vec2 coords) const;
};

#endif