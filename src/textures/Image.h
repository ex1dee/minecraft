#ifndef IMAGE_H
#define IMAGE_H

#include "../../dependencies/stb_image.h"

class Image {
	Image();
public:
	unsigned char* data;
	int width;
	int height;
	int nchannels;

	Image(const char* path, bool flip) {
		stbi_set_flip_vertically_on_load(flip);
		data = stbi_load(path, &width, &height, &nchannels, 0);
	}

	~Image() {
		free();
	}

	void free() {
		stbi_image_free(data);
	}
};

#endif