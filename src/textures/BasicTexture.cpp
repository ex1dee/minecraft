#include "BasicTexture.h"

#include <glad/glad.h>
#include <iostream>

#include "Image.h"
#include "TextureManager.h"

BasicTexture::BasicTexture(const char* path, bool flip) {
	this->path = path;
	this->type = GL_TEXTURE_2D;

	load(flip);
}

void BasicTexture::load(bool flip) {
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	glActiveTexture(GL_TEXTURE0);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MAX_LEVEL, 1);

	Image image(path, flip);

	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		if (format) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
			
			glGenerateMipmap(type);
		} else {
			std::cout << "Unsupported number of channels " << image.nchannels << " in file \"" << path << "\"\n";
		}
	} else {
		std::cout << "Failed to load texture \"" << path << "\"\n";
	}
}