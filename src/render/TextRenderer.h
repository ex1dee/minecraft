#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "../player/Camera.h"
#include "../text/Text2D.h"

class TextRenderer {
	std::vector<Text2D*> texts;
	Shader* activeShader;

	void updateShader(const Camera& camera);
public:
	void render(const Camera& camera);
	void add(Text2D* text);
};

#endif