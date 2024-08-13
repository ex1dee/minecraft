#include "CubeTexture.h"

#include "../utils/Files.h"
#include "TextureManager.h"
#include "Image.h"

CubeTexture::CubeTexture(const std::string& directory, std::array<std::string, 6>& fileNames, bool flip)
	: Texture(GL_TEXTURE_CUBE_MAP, TextureType::CUBEMAP) {
	this->filePaths = filePaths;
	
	for (int i = 0; i < fileNames.size(); ++i) {
		filePaths[i] = Files::getFullPath(directory, fileNames[i]);
	}

	load(flip);
}

void CubeTexture::load(bool flip) {
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	for (int i = 0; i < 6; ++i) {
		Texture::load(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, filePaths[i], flip);
	}
}