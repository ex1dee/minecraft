#include "Texture.h"

#include "TextureManager.h"
#include "Image.h"

void Texture::load(GLenum target, const char* path, bool flip) {
	Image image(path, flip);

	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		width = image.width;
		height = image.height;

		if (format) {
			glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.data);
		} else {
			std::cout << "Unsupported number of channels " << image.nchannels << " in file \"" << path << "\"\n";
		}
	} else {
		std::cout << "Failed to load texture \"" << path << "\"\n";
	}
}