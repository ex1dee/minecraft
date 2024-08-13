#include "SpriteRenderer.h"

#include "Renderer.h"

void SpriteRenderer::render(const Sun* sun) {
	startRender(true, sun);

	for (Sprite* sprite : sprites) {
		sprite->draw(activeShader);
	}

	sprites.clear();

	finishRender();
}

void SpriteRenderer::startRender(bool depthTest, const Sun* sun) {
	updateShader(sun);

	if (!depthTest)
		glDisable(GL_DEPTH_TEST);

	Renderer::startTransparentRender();
}

void SpriteRenderer::updateShader(const Sun* sun) {
	activeShader = ShadersDatabase::get(ShaderType::SPRITE);
	activeShader->use();

	activeShader->setMat4("projection", GUI::getProjection());
	activeShader->setMat4("view", GUI::getView());

	if (sun != nullptr) {
		activeShader->setBool("sunEnabled", true);
		activeShader->setVec3("sunDirection", sun->getLight().direction);
	} else {
		activeShader->setBool("sunEnabled", false);
	}
}

void SpriteRenderer::finishRender() {
	Renderer::finishTransparentRender();
	glEnable(GL_DEPTH_TEST);
}

void SpriteRenderer::add(Sprite* sprite) {
	if (sprite->texture.data != nullptr)
		sprites.push_back(sprite);
}