#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include <string>
#include <array>

#include "Texture.h"

class CubeTexture : public Texture {
	void load(const std::string& directory, const std::array<std::string, 6>& fileNames, bool flip);
public:
	CubeTexture(const std::string& directory, const std::array<std::string, 6>& fileNames, bool flip);
};

#endif