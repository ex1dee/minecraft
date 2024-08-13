#ifndef CUBETEXTURE_H
#define CUBETEXTURE_H

#include <glad/glad.h>

#include <string>
#include <array>

#include "Texture.h"

class CubeTexture : public Texture {
	std::array<std::string, 6> filePaths;

	void load(bool flip);
public:
	CubeTexture(const std::string& directory, std::array<std::string, 6>& fileNames, bool flip);
};

#endif