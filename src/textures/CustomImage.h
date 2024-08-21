#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include <vector>

#include "Image.h"

template<typename Td>
class CustomImage : public Image {
	GLenum type;
public:
	Td* data;

	CustomImage(GLenum type, int width, int height, int nchannels)
		: Image(width, height, nchannels), type(type) {
		data = new Td[width * height * nchannels + 1];
		data[width * height * nchannels] = '\0';
	}

	GLenum getType() const {
		return type;
	}

	void free() override {
		delete[] data;
	}
};

#endif