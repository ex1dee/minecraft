#ifndef FTLOADER_H
#define FTLOADER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <unordered_map>

#include "FTCharacter.h"

constexpr const char* FONT_MINECRAFTIAREGULAR_PATH = "resources/fonts/MinecraftiaRegular.ttf";
constexpr CharacterType UNKNOWN_SYMBOL = L'∅';
constexpr float GLYPH_SIZE_PX = 128;

class FTLoader {
	static std::unordered_map<CharacterType, FTCharacter*> chars;
	static FT_Library ft;
	static FT_Face face;

	static void loadChar(CharacterType c);
public:
	static void initialize();
	static void finalize();

	static void load(const std::string& path);
	static const FTCharacter& getCharacter(CharacterType c);
};

#endif