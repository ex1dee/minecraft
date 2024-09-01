#ifndef CUSTOMTEXTURE_H
#define CUSTOMTEXTURE_H

#include "Texture.h"

template <typename Td>
class CustomTexture : public Texture {
	void load(const CustomImage<Td>& image, GLint wrap, GLint filter);
public:
	CustomTexture() {}
	CustomTexture(const CustomImage<Td>& image, GLint wrap, GLint filter, bool unloadImage = false);
};

#endif