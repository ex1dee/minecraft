#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "../gui/GUI.h"

class GUIRenderer {
	Shader* activeShader;

	void updateShader();
	void render(GUISector* sector);
public:
	void render();
};

#endif