#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include <string>
#include <array>

#include "Texture.h"

class CubeTexture : public Texture {
	std::array<std::string, 6> filePaths;

	void load(bool flip);
public:
	CubeTexture(const char* directory, std::array<const char*, 6>& fileNames, bool flip);
};

#endif