#include "Texture.h"

Texture::Texture(GLenum target, TextureType type, bool unloadImage)
	: target(target), type(type), unloadImage(unloadImage) {

}

void Texture::load(GLenum target, const std::string& path, bool flip) {
	image = Image(path, flip);
	
	if (image.data) {
		GLenum format = TextureManager::getFormat(image.nchannels);

		if (!format) {
			std::cerr << "Unsupported number of channels " << image.nchannels << " in file \"" << path << "\"\n";
		}

		GL(glTexImage2D(target, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data));
		align();
	} else {
		std::cerr << "Failed to load texture \"" << path << "\"\n" << stbi_failure_reason();
	}

	if (unloadImage)
		image.free();
}

void Texture::align() {
	if (image.width % 4 != 0)
		glPixelStorei(GL_UNPACK_ALIGNMENT, image.nchannels);
}

glm::vec4 Texture::getColor(int x, int y) {
	int index = y * image.width * image.nchannels + x * image.nchannels;

	return glm::vec4(
		(float)image.data[index] / 255.0f, 
		(float)image.data[index + 1] / 255.0f, 
		(float)image.data[index + 2] / 255.0f, 
		(float)image.data[index + 3] / 255.0f
	);
}