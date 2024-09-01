#ifndef BASICTEXTURE_H
#define BASICTEXTURE_H

#include "Texture.h"

class BasicTexture : public Texture {
	std::string path;

	void load(bool flip);
public:
	BasicTexture() {}
	BasicTexture(const std::string& path, bool flip, TextureType type, bool unloadImage = true);
};

#endif