#include "GUIRenderer.h"

#include "../shaders/ShadersDatabase.h"

void GUIRenderer::render() {
	startRender(false);

	render(&GUIDatabase::root);

	finishRender();
}

void GUIRenderer::render(GUISector* sector) {
	for (auto pair : *sector) {
		GUIElement* element = pair.second;

		if (element->hasTexture)
			element->sprite->draw(activeShader);

		render(&element->children);
	}
}