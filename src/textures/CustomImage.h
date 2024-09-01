#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include <vector>
#include <memory>

#include "Image.h"

template<typename Td>
class CustomImage : public Image {
	GLenum type;

	struct ImageDataDeleter {
	public:
		void operator() (Td* data) {
			delete[] data;
		}
	};

	using imageData = std::unique_ptr<Td[], ImageDataDeleter>;

	imageData data;
public:
	CustomImage(GLenum type, int width, int height, int nchannels)
		: Image(width, height, nchannels), type(type) {
		
	}

	CustomImage& operator=(CustomImage&& other) = default;

	GLenum getType() const {
		return type;
	}

	Td& operator[](int index) {
		return data[index];
	}

	bool empty() const {
		return data == nullptr;
	}

	int getSize() const {
		return width * height * nchannels;
	}

	const Td* const getRawData() const {
		return data.get();
	}

	void copyData(Td* data) {
		int size = getSize();

		Td* rawData = new Td[size + 1];
		memcpy(rawData, data, size);

		allocData(rawData);
	}

	void allocData(Td* data = nullptr) {
		int size = getSize();

		if (data == nullptr)
			data = new Td[size + 1];

		this->data = imageData(data);
		this->data[size] = '\0';
	}

	void free() override {
		data.reset();
	}
};

#endif