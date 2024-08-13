#include "CustomTexture.h"

CustomTexture::CustomTexture(const CustomImage& image, GLint wrap, GLint filter)
	: Texture(GL_TEXTURE_2D, TextureType::CUSTOM) {
	load(image, wrap, filter);
}

void CustomTexture::load(const CustomImage& image, GLint wrap, GLint filter) {
	GL(glGenTextures(1, &ID));
	GL(glBindTexture(target, ID));

	GL(glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap));
	GL(glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap));
	GL(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter));
	GL(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter));

	Texture::load(image);
}