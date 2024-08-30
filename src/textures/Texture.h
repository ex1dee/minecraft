#ifndef TEXTURE_H
#define TEXTURE_H

#include "../GL/GLHelper.h"
#include "TextureManager.h"
#include <cstdint>

#include "TextureType.h"
#include "CustomImage.h"

class Texture {
protected:
	uint32_t ID;
	TextureType type;
	GLenum target;
	int width;
	int height;
	int nchannels;

	void align();
	void prepare(const Image& image);
	void load(GLenum target, const std::string& path, bool flip);

	template<typename Td> 
	void load(const CustomImage<Td>& image) {
		prepare(image);

		if (!image.empty()) {
			GLenum format = TextureManager::getFormat(image.nchannels);

			if (!format) {
				std::cerr << "Unsupported number of channels in a custom texture\n";
			}

			GL(glTexImage2D(target, 0, format, width, height, 0, format, image.getType(), image.getRawData()));
			align();
		}
	}
public:
	Texture() {}
	Texture(GLenum target, TextureType type)
		: target(target), type(type) {}
	virtual ~Texture() = default;

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	uint32_t getID() const { return ID; }
	GLenum getTarget() const { return target; }
	TextureType getType() const { return type; }
};

#endif