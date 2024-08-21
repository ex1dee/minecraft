#include "FTLoader.h"

std::unordered_map<CharacterType, std::unique_ptr<FTCharacter>> FTLoader::chars;
FT_Library FTLoader::ft;
FT_Face FTLoader::face;

constexpr std::uint32_t
PIXEL_WIDTH = 0,
PIXEL_HEIGHT = 48,
CHARS_NUMBER = 65535;

void FTLoader::initialize() {
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE\n" << "Could not init FreeType library\n";

	load(FONT_MINECRAFTIAREGULAR_PATH);
}

void FTLoader::finalize() {
	FT_Done_FreeType(ft);
}

void FTLoader::load(const std::string& path) {
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE\n" << "Failed to load font at " << path << "\n";

	FT_Set_Pixel_Sizes(face, 0, GLYPH_SIZE_PX);
	
	for (int c = 0; c < CHARS_NUMBER; ++c) {
		loadChar(c);
	}

	FT_Done_Face(face);
}

void FTLoader::loadChar(CharacterType c) {
	if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		std::cout << "ERROR::FREETYPE\n" << "Failed to load glyph ";
		std::wcout << c << "\n";
	}
	
	FT_Bitmap& bitmap = face->glyph->bitmap;

	if (!face->glyph->bitmap.buffer && c != L' ')
		return;

	CustomImage<std::uint8_t> image(GL_UNSIGNED_BYTE, bitmap.width, bitmap.rows, 1);
	image.data = face->glyph->bitmap.buffer;
	
	std::shared_ptr<CustomTexture<std::uint8_t>> texture = std::make_shared<CustomTexture<std::uint8_t>>(image, GL_CLAMP_TO_EDGE, GL_LINEAR);
	
	FTCharacter* ftChar = new FTCharacter{
		texture,
		c,
		glm::ivec2(face->glyph->advance.x, face->glyph->advance.y),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows)
	};

	chars.emplace(c, ftChar);
}

const FTCharacter& FTLoader::getCharacter(CharacterType c) {
	if (chars.find(c) == chars.end())
		return *chars[UNKNOWN_SYMBOL];

	return *chars[c];
}