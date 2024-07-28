#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include <array>

#include "Texture.h"

class CubeTexture : public Texture {
	std::array<const char*, 6> filePaths;

	void load(bool flip);
public:
	CubeTexture(std::array<const char*, 6>& path, bool flip);
};

#endif