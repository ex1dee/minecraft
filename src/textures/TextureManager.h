#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>
#include <string>

#include "../shaders/Shader.h"
#include "Texture.h"

class TextureManager {
public:
	static GLenum getFormat(int nchannels);
	static void bindTexture(const Texture& texture, Shader& shader, std::string uniform);
	static void bindDepthMap(unsigned int depthMap, Shader& shader, std::string uniform);
	static void bindTexture(unsigned int textureID, Shader& shader, std::string uniform, GLenum target);
};

#endif