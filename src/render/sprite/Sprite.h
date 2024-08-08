#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>

#include "../../math/geometry/Transform.h"
#include "../../shaders/Shader.h"
#include "SpriteTexture.h"
#include "../Drawable.h"

class Sprite : public Drawable {
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<unsigned int> indices;

	void calcVertices();
	void calcTextureCoords();
	void bindTexture(Shader* shader);
public:
	SpriteTexture texture;
	Transform transform;

	glm::vec4 color = glm::vec4(1);

	void setup() override;
	void reset() override;
	void draw(Shader* shader) override;
};

#endif