#include "TextureManager.h"

GLenum TextureManager::getFormat(int nchannels) {
	if (nchannels == 3)
		return GL_RGB;
	else if (nchannels == 4)
		return GL_RGBA;
	else
		return NULL;
}

void TextureManager::bindTexture(const Texture& texture, Shader& shader, std::string uniform) {
	bindTexture(texture.getID(), shader, uniform, texture.getTarget());
}

void TextureManager::bindDepthMap(unsigned int depthMap, Shader& shader, std::string uniform) {
	bindTexture(depthMap, shader, uniform, GL_TEXTURE_2D);
}

void TextureManager::bindTexture(unsigned int textureID, Shader& shader, std::string uniform, GLenum target) {
	int id = shader.getCurrentTextureID();

	shader.use();
	shader.setSampler(uniform.c_str(), id);

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(target, textureID);

	shader.incrementCurrentTextureID();
}