#include "TextRenderer.h"

#include "Renderer.h"

void TextRenderer::render(const Camera& camera) {
	Renderer::startTransparentRender();
	updateShader(camera);

	for (Text2D* text : texts) {
		text->draw(*activeShader);
	}

	texts.clear();

	Renderer::finishTransparentRender();
}

void TextRenderer::updateShader(const Camera& camera) {
	activeShader = &ShadersDatabase::get(ShaderType::TEXT);
	activeShader->use();

	activeShader->setMat4("projection", camera.getProjection());
	activeShader->setMat4("view", camera.getView());
}

void TextRenderer::add(Text2D& text) {
	if (!text.getText().empty())
		texts.push_back(&text);
}