#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include "Image.h"

class CustomImage : public Image {
public:
	float* data;

	CustomImage(int width, int height, int nchannels)
		: Image(width, height, nchannels) {
		allocData();
	}

	void allocData() {
		data = new float[width * height * nchannels];
	}

	void free() override {
		if (data != nullptr)
			delete data;
	}
};

#endif