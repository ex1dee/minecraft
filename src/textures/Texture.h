#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <cstdint>

#include "TextureType.h"

class Texture {
protected:
	uint32_t ID;
	TextureType type;
	GLenum target;
	int width;
	int height;

	void load(GLenum target, const char* path, bool flip);
public:
	Texture() {}
	Texture(GLenum target, TextureType type)
		: target(target), type(type) {}

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	uint32_t getID() const { return ID; }
	GLenum getTarget() const { return target; }
	TextureType getType() const { return type; }
};

#endif