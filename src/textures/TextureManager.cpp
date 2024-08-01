#include "TextureManager.h"

GLenum TextureManager::getFormat(int nchannels) {
	if (nchannels == 3)
		return GL_RGB;
	else if (nchannels == 4)
		return GL_RGBA;
	else
		return NULL;
}

void TextureManager::bindTexture(Texture& texture, Shader& shader, const char* uniform, int id) {
	shader.use();
	shader.setInt(uniform, id);

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(texture.getType(), texture.getID());
}

void TextureManager::bindDepthMap(unsigned int depthMap, Shader& shader, const char* uniform, int id) {
	shader.use();
	shader.setInt(uniform, id);

	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, depthMap);
}