#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "../gui/GUI.h"

class GUIRenderer {
	Shader* spriteShader;
	Shader* textShader;

	void updateTextShader();
	void updateSpriteShader();
	void render(GUISector* sector, int layer = 0);
public:
	void render();
};

#endif