#include "Texture.h"

#include "TextureManager.h"

void Texture::load(GLenum target, const std::string& path, bool flip) {
	Image image(path, flip);
	prepare(image);

	this->target = target;

	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		if (!format) {
			std::cout << "Unsupported number of channels " << image.nchannels << " in file \"" << path << "\"\n";
		}

		glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.data);
	} else {
		std::cout << "Failed to load texture \"" << path << "\"\n";
	}
}

void Texture::load(const CustomImage& image) {
	this->target = GL_TEXTURE_2D;
	prepare(image);

	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		if (!format) {
			std::cout << "Unsupported number of channels in custom texture\n";
		}

		glTexImage2D(target, 0, format, width, height, 0, format, GL_FLOAT, image.data);
	} else {
		std::cout << "Failed to load custom texture\n";
	}
}

void Texture::prepare(const Image& image) {
	width = image.width;
	height = image.height;
	nchannels = image.nchannels;
}