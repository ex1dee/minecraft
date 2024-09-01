#ifndef TEXTURE_H
#define TEXTURE_H

#include "../GL/GLHelper.h"
#include "TextureManager.h"
#include <cstdint>

#include "TextureType.h"
#include "CustomImage.h"
#include "Image.h"

class Texture {
protected:
	uint32_t ID;
	bool unloadImage;
	TextureType type;
	GLenum target;
	Image image;

	void align();
	void load(GLenum target, const std::string& path, bool flip);

	template<typename Td>
	void load(const CustomImage<Td>& image) {
		this->image = image;

		if (!image.empty()) {
			GLenum format = TextureManager::getFormat(image.nchannels);

			if (!format) {
				std::cerr << "Unsupported number of channels in a custom texture\n";
			}

			GL(glTexImage2D(target, 0, format, image.width, image.height, 0, format, image.getType(), image.getRawData()));
			align();
		}

		if (unloadImage)
			this->image.free();
	}
public:
	Texture() {}
	Texture(GLenum target, TextureType type, bool unloadImage = true);
	virtual ~Texture() = default;

	uint32_t getID() const { return ID; }
	GLenum getTarget() const { return target; }
	TextureType getType() const { return type; }
	int getWidth() const { return image.width; }
	int getHeight() const { return image.height; }
	const unsigned char* const getData() const { return image.data; }

	glm::vec4 getColor(int x, int y);
};

#endif