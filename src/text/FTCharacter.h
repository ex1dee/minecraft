#ifndef FTCHARACTER_H
#define FTCHARACTER_H

#include <glm/glm.hpp>

#include "../textures/CustomTexture.h"

typedef wchar_t CharacterType;

class FTCharacter {
public:
	std::shared_ptr<CustomTexture<std::uint8_t>> texture;
	CharacterType glyph;
	glm::ivec2 advance;
	glm::ivec2 bearing;
	glm::ivec2 size;
};

#endif