#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "SpriteRenderer.h"
#include "../gui/GUI.h"

class GUIRenderer : public SpriteRenderer {
	void render(GUISector* sector);
public:
	void render();
};

#endif