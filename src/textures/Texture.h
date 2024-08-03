#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "TextureType.h"

class Texture {
protected:
	unsigned int ID;
	TextureType type;
	GLenum target;
public:
	Texture() {}
	Texture(GLenum target, TextureType type)
		: target(target), type(type) {}

	unsigned int getID() const { return ID; }

	TextureType getType() const { return type; }

	GLenum getTarget() const { return target; }
};

#endif