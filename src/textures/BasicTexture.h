#ifndef BASICTEXTURE_H
#define BASICTEXTURE_H

#include "Texture.h"

class BasicTexture : public Texture {
	const char* path;

	void load(bool flip);
public:
	BasicTexture() = default;
	BasicTexture(const char* path, bool flip);
};

#endif