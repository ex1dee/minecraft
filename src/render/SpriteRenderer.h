#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <vector>

#include "../render/sprite/Sprite.h"
#include "../shaders/ShaderType.h"
#include "../shaders/Shader.h"
#include "../world/Sun.h"

class SpriteRenderer {
	std::vector<Sprite*> sprites;

	void updateShader(const Sun* sun);
protected:
	Shader* activeShader;

	void startRender(bool depthTest, const Sun* sun = nullptr);
	void finishRender();
public:
	void render(const Sun* sun);
	void add(Sprite* sprite);
};

#endif