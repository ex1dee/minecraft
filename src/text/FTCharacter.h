#ifndef FTCHARACTER_H
#define FTCHARACTER_H

#include <glm/glm.hpp>

#include "../textures/CustomTexture.h"
#include "../utils/PointerUtils.h"

typedef wchar_t CharacterType;

class FTCharacter {
public:
	CustomTexture<std::uint8_t>* texture;
	CharacterType glyph;
	glm::ivec2 advance;
	glm::ivec2 bearing;
	glm::ivec2 size;

	~FTCharacter() {
		freePointer(&texture);
	}
};

#endif