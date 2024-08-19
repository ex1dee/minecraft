#include "Texture.h"

void Texture::load(GLenum target, const std::string& path, bool flip) {
	Image image(path, flip);
	prepare(image);

	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		if (!format) {
			std::cout << "Unsupported number of channels " << image.nchannels << " in file \"" << path << "\"\n";
		}

		GL(glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.data));
		align();
	} else {
		std::cout << "Failed to load texture \"" << path << "\"\n" << stbi_failure_reason();
	}
}

void Texture::align() {
	if (width % 4 != 0)
		glPixelStorei(GL_UNPACK_ALIGNMENT, nchannels);
}

void Texture::prepare(const Image& image) {
	width = image.width;
	height = image.height;
	nchannels = image.nchannels;
}