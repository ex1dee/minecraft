#include "CubeTexture.h"

#include <glad/glad.h>
#include <iostream>

#include "Image.h"
#include "TextureManager.h"

CubeTexture::CubeTexture(std::array<const char*, 6>& filePaths, bool flip)
	: Texture(GL_TEXTURE_CUBE_MAP) {
	this->filePaths = filePaths;
	
	load(flip);
}

void CubeTexture::load(bool flip) {
	glGenTextures(1, &ID);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	for (int i = 0; i < 6; ++i) {
		Image image(filePaths[i], flip);

		if (image.data) {
			GLenum format = TextureManager::getFormat(image.nchannels);

			if (format) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
			} else {
				std::cout << "Unsupported number of channels " << image.nchannels << " in file \"" << filePaths[i] << "\"\n";
			}
		} else {
			std::cout << "Failed to load texture \"" << filePaths[i] << "\"\n";
		}
	}
}