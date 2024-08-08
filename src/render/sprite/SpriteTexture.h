#ifndef SPRITETEXTURE_H
#define SPRITETEXTURE_H

#include "../../textures/Texture.h"
#include "../../textures/AtlasCoords.h"

class SpriteTexture {
public:
	const Texture* data;
	AtlasCoords atlas;
	bool useAtlas;

	glm::vec2 getSize() {
		if (useAtlas) {
			return glm::abs(atlas.topRight * (float) data->getWidth() - atlas.bottomLeft * (float)data->getWidth());
		} else {
			return glm::vec2(
				data->getWidth(),
				data->getHeight()
			);
		}
	}
};

#endif