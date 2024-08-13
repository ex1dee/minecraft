#include "CustomTexture.h"

CustomTexture::CustomTexture(const CustomImage& image, GLint wrap, GLint filter)
	: Texture(GL_TEXTURE_2D, TextureType::CUSTOM) {
	load(image, wrap, filter);
}

void CustomTexture::load(const CustomImage& image, GLint wrap, GLint filter) {
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);

	Texture::load(image);
}