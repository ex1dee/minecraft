#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <vector>

#include "../render/sprite/Sprite.h"
#include "../shaders/ShaderType.h"
#include "../shaders/Shader.h"
#include "../world/Sun.h"

class SpriteRenderer {
	std::vector<Sprite*> sprites;
	Shader* activeShader;

	void updateShader(const Sun& sun, const Camera& camera);
public:
	void render(const Sun& sun, const Camera& camera);
	void add(Sprite& sprite);
};

#endif