#ifndef SPRITE_H
#define SPRITE_H

#include "../../GL/GLHelper.h"

#include "../../math/geometry/Transform.h"
#include "../../math/shapes/Rect.h"
#include "../../textures/SpriteTexture.h"
#include "../../shaders/Shader.h"
#include "../Drawable.h"

class Sprite : public Drawable {
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<uint32_t> indices;

	void calcVertices();
	void calcTextureCoords();
	void bindTexture(Shader& shader);
public:
	glm::vec4 color = glm::vec4(1);
	SpriteTexture texture;
	Transform transform;

	Sprite() = default;
	Sprite(const Sprite& other);

	void setup() override;
	void reset() override;
	void draw(Shader& shader) override;

	void resetTexture();
	Rect&& getRect();
};

#endif