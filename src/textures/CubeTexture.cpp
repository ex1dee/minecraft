#include "CubeTexture.h"

#include "../utils/Files.h"
#include "TextureManager.h"
#include "Image.h"

CubeTexture::CubeTexture(const std::string& directory, const std::array<std::string, 6>& fileNames, bool flip)
	: Texture(GL_TEXTURE_CUBE_MAP, TextureType::CUBEMAP) {
	load(directory, fileNames, flip);
}

void CubeTexture::load(const std::string& directory, const std::array<std::string, 6>& fileNames, bool flip) {
	GL(glGenTextures(1, &ID));
	GL(glBindTexture(target, ID));

	GL(glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GL(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

	for (int i = 0; i < fileNames.size(); ++i) {
		Texture::load(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
			Files::getFullPath(directory, fileNames[i]),
			flip
		);
	}
}