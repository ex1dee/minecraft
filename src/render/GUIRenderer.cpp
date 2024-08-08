#include "GUIRenderer.h"

#include "../shaders/ShadersDatabase.h"
#include "../render/Renderer.h"

void GUIRenderer::render() {
	updateShader();

	glDisable(GL_DEPTH_TEST);
	Renderer::startTransparentRender();

	render(&GUIDatabase::root);

	Renderer::finishTransparentRender();
	glEnable(GL_DEPTH_TEST);
}

void GUIRenderer::updateShader() {
	activeShader = ShadersDatabase::get(ShaderType::SPRITE);
	activeShader->use();

	activeShader->setMat4("projection", GUI::getProjection());
	activeShader->setMat4("view", GUI::getView());
}

void GUIRenderer::render(GUISector* sector) {
	for (auto pair : *sector) {
		GUIElement* element = pair.second;

		if (element->hasTexture)
			element->sprite->draw(activeShader);

		render(&element->children);
	}
}