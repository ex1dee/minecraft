#ifndef IMAGE_H
#define IMAGE_H

#include <glad/glad.h>
#include <string>

#include "../../dependencies/stb_image.h"

class Image {
public:
	unsigned char* data;
	int width;
	int height;
	int nchannels;
	
	Image() {}

	Image(int width, int height, int nchannels)
		: width(width), height(height), nchannels(nchannels) {

	}

	Image(const std::string& path, bool flip) {
		load(path, flip);
	}

	void load(const std::string& path, bool flip) {
		stbi_set_flip_vertically_on_load(flip);
		data = stbi_load(path.c_str(), &width, &height, &nchannels, STBI_default);
	}

	virtual void free() {
		if (data != nullptr)
			delete data;
	}
};

#endif