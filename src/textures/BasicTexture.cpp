#include "BasicTexture.h"

BasicTexture::BasicTexture(const std::string& path, bool flip, TextureType type)
	: Texture(GL_TEXTURE_2D, type) {
	this->path = path;

	load(flip);
}

void BasicTexture::load(bool flip) {
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, 1);

	Texture::load(GL_TEXTURE_2D, path, flip);

	glGenerateMipmap(target);
}