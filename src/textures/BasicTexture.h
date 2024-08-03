#ifndef BASICTEXTURE_H
#define BASICTEXTURE_H

#include "Texture.h"

class BasicTexture : public Texture {
	const char* path;

	void load(bool flip);
public:
	BasicTexture() {}
	BasicTexture(const char* path, bool flip, TextureType type);
};

#endif