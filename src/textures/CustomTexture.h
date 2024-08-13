#ifndef CUSTOMTEXTURE_H
#define CUSTOMTEXTURE_H

#include "Texture.h"

class CustomTexture : public Texture {
	void load(const CustomImage& image, GLint wrap, GLint filter);
public:
	CustomTexture() {}
	CustomTexture(const CustomImage& image, GLint wrap, GLint filter);
};

#endif