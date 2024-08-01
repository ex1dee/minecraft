#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>

#include "../shaders/Shader.h"
#include "Texture.h"

class TextureManager {
public:
	static GLenum getFormat(int nchannels);
	static void bindTexture(Texture& texture, Shader& shader, const char* uniform, int id);
	static void bindDepthMap(unsigned int depthMap, Shader& shader, const char* uniform, int id);
};

#endif