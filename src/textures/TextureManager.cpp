#include "TextureManager.h"

#include "Texture.h"

GLenum TextureManager::getFormat(int nchannels) {
	if (nchannels == 4)
		return GL_RGBA;
	else if (nchannels == 3)
		return GL_RGB;
	else if (nchannels == 1)
		return GL_RED;
	else
		return NULL;
}

void TextureManager::bindTexture(const Texture* texture, Shader& shader, const std::string& uniform) {
	bindTexture(texture->getID(), shader, uniform, texture->getTarget());
}

void TextureManager::bindDepthMap(uint32_t depthMap, Shader& shader, const std::string& uniform) {
	bindTexture(depthMap, shader, uniform, GL_TEXTURE_2D);
}

void TextureManager::bindTexture(uint32_t textureID, Shader& shader, const std::string& uniform, GLenum target) {
	int id = shader.getCurrentTextureID();

	shader.use();
	shader.setSampler(uniform.c_str(), id);

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(target, textureID);

	shader.incrementCurrentTextureID();
}