#include "GUIRenderer.h"

#include "../shaders/ShadersDatabase.h"
#include "Renderer.h"

void GUIRenderer::render() {
	Renderer::startTransparentRender();
	glDepthMask(GL_TRUE);

	updateSpriteShader();
	updateTextShader();

	render(&GUIDatabase::root);
	
	Renderer::finishTransparentRender();
}

void GUIRenderer::updateSpriteShader() {
	spriteShader = &ShadersDatabase::get(ShaderType::SPRITE);
	spriteShader->use();

	spriteShader->setMat4("projection", GUI::getProjection());
	spriteShader->setMat4("view", GUI::getView());

	spriteShader->setBool("sunEnabled", false);
}

void GUIRenderer::updateTextShader() {
	textShader = &ShadersDatabase::get(ShaderType::TEXT);
	textShader->use();

	textShader->setMat4("projection", GUI::getProjection());
	textShader->setMat4("view", GUI::getView());
}

void GUIRenderer::render(GUISector* sector, int layer) {
	for (auto pair : *sector) {
		GUIElement& element = *pair.second;

		if (!element.visible)
			continue;

		float z = GUI_ELEMENT_Z + (layer + element.layer_offset) * GUI_ELEMENT_LAYER_Z_OFFSET;

		if (element.hasTexture()) {
			spriteShader->use();

			element.sprite->transform.position.z = z;
			element.sprite->draw(*spriteShader);
		}

		if (element.hasText()) {
			textShader->use();

			const glm::vec3& textPos = element.text->getPosition();
			element.text->setPosition(glm::vec3(textPos.x, textPos.y, z));
			element.text->draw(*textShader);
		}

		render(&element.children, layer + element.layer_offset + 1);
	}
}