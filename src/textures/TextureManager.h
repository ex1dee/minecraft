#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glad/glad.h>

#include "../shaders/Shader.h"

class Texture;

class TextureManager {
public:
	static GLenum getFormat(int nchannels);
	static void bindTexture(const Texture* texture, Shader& shader, const std::string& uniform);
	static void bindDepthMap(uint32_t depthMap, Shader& shader, const std::string& uniform);
	static void bindTexture(uint32_t textureID, Shader& shader, const std::string& uniform, GLenum target);
};

#endif