#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include "Image.h"

template<typename Td>
class CustomImage : public Image {
	GLenum type;
public:
	Td* data;

	CustomImage(GLenum type, int width, int height, int nchannels)
		: Image(width, height, nchannels), type(type) {
		allocData();
	}

	void allocData() {
		data = new Td[width * height * nchannels];
	}

	GLenum getType() const {
		return type;
	}

	void free() override {
		freePointer(&data);
	}
};

#endif